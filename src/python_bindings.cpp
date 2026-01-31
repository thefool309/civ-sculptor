#include "CoutRedirect.h"
#include "include/World.h"
#include <Simulation.h>
#include <atomic>
#include <iostream>
#include <pybind11/iostream.h> // Add this include at the top of the file
#include <pybind11/pybind11.h>

#include <thread>

namespace py = pybind11;

/// <summary>
/// SimulationApi is an abstraction created to create python bindings to these
/// c++ libraries.
/// </summary>
class SimulationApi {
private:
  Simulation sim;
  CoutRedirect cout_redirect;
  std::atomic<bool> runningSim{false};
  std::thread simThread;

public:
  SimulationApi(uint64_t seed, std::string name) : sim(WorldSeed(seed, name)) {}
  ~SimulationApi() { join(); }

  std::string poll_log() { return cout_redirect.take(); }

  bool getRunningSim() { return runningSim.load(std::memory_order_acquire); }

  /// <summary>
  /// set the runningSim bool to the param value
  /// </summary>
  /// <param name="_running">value to set runningSim to</param>
  void setRunningSim(bool _running) {
    runningSim.store(_running, std::memory_order_release);
  }
  /// <summary>
  /// The main python entrypoint to the simulation. will be used later for logic
  /// on running the simulation x amount of ticks at a time
  /// </summary>
  /// <param name="ticks"> - the number of ticks to progress the
  /// simulation</param>
  void startSimulation(uint64_t ticks) {
    std::cout << "`startSimulation()` called!\n";
    if (!runningSim) {
      setRunningSim(true); // toggleRunningSim on
    }
    sim.Generate3Civs();
    sim.SimLoop(ticks);
    setRunningSim(false); // done so toggle running sim off
  }
  /// <summary>
  /// Generates 3 civilizataions for the simulation. Asynchronous function using
  /// member field std::thread simThread.
  /// </summary>
  void generate3Civs() {
    if (simThread.joinable())
      join(); // join thread if it hasn't been joined already
    simThread = std::thread([this]() { sim.Generate3Civs(); });
  }
  /// <summary>
  /// Generates 5 civilizataions for the simulation. Asynchronous function using
  /// member field std::thread simThread.
  /// </summary>
  void generate5Civs() {
    if (simThread.joinable())
      join();
    simThread = std::thread([this]() { sim.Generate5Civs(); });
  }
  /// <summary>
  /// Generates 10 civilizataions for the simulation. Asynchronous function
  /// using member field std::thread simThread.
  /// </summary>
  void generate10Civs() {
    if (simThread.joinable())
      join();
    simThread = std::thread([this]() { sim.Generate10Civs(); });
  }
  /// <summary>
  ///	starts the simulation for `ticks` number of ticks on a seperate thread
  /// </summary>
  /// <param name="ticks"> - the number of ticks to run the simulation
  /// for</param>
  void startSimulationAsync(uint64_t ticks) {
    if (runningSim)
      return;
    if (simThread.joinable())
      join();
    setRunningSim(true);

    simThread = std::thread([this, ticks]() {
      // RAII Guard
      // just a small struct with a destructor that sets the flag to false
      // that way if it goes out of scope it sets itself to false;
      struct Guard {
        std::atomic<bool> &flag;
        ~Guard() { flag.store(false, std::memory_order_release); }
      } guard{runningSim};

      sim.SimLoop(ticks);
      setRunningSim(false);
    });
  }
  /// <summary>
  /// Joins running threads
  /// </summary>
  void join() {
    if (simThread.joinable()) {
      simThread.join();
    }
  }
};

PYBIND11_MODULE(civ_module, m) {
  m.doc() = "Module for binding sim to python"; // Optional module docstrin
  py::class_<SimulationApi>(m, "SimulationApi")
      .def(py::init<const uint64_t,
                    const std::string>()) // gil_scoped_release prevents
                                          // blocking python so you can
                                          // multithread the python script
      .def("startSimulation", &SimulationApi::startSimulation,
           py::call_guard<py::gil_scoped_release>(), py::arg("ticks"),
           "Spins up the simulation and runs for ticks")
      .def("startSimulationAsync", &SimulationApi::startSimulationAsync,
           py::arg("ticks"), py::call_guard<py::gil_scoped_release>())
      .def("poll_log", &SimulationApi::poll_log)
      .def("generate3Civs", &SimulationApi::generate3Civs)
      .def("generate5Civs", &SimulationApi::generate5Civs)
      .def("generate10Civs", &SimulationApi::generate10Civs)
      .def_property("runningSim", &SimulationApi::getRunningSim,
                    &SimulationApi::setRunningSim);
}
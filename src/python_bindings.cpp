/// @file python_bindings.cpp
/// @brief pybind11 bindings exposing SimulationApi to python

#include <pybind11/pybind11.h>
#include <pybind11/iostream.h> // Add this include at the top of the file
#include "include/World.h"
#include "include/Civilization.h"
#include "CoutRedirect.h"
#include "include/World.h"
#include <Simulation.h>
#include <atomic>
#include <iostream>
#include <pybind11/iostream.h> // Add this include at the top of the file
#include <pybind11/pybind11.h>

#include <thread>

namespace py = pybind11;

/// @brief python-facing API wrapper around the Simulation engine
///
/// provides a simplified interface for controlling the simulation from python.
/// handles cout redirection for log polling and supports both synchronous
/// and asynchronous execution modes via std::thread.
class SimulationApi {
private:
	Simulation sim;                    ///< the underlying simulation engine
	CoutRedirect cout_redirect;        ///< captures cout output for python polling
	std::atomic<bool> runningSim{ false }; ///< whether the sim is currently running
	std::thread simThread;             ///< thread for async execution
public:
	/// @param seed rng seed for the world
	/// @param name world name
	SimulationApi(uint64_t seed, std::string name) : sim(WorldSeed(seed, name)) {}

	/// @brief join any running sim thread on destruction
	~SimulationApi() { join(); }

	/// @brief take all captured cout output since last poll
	/// @return captured log string
	std::string poll_log() {
		return cout_redirect.take();
	}

	/// @return whether the simulation is currently running
	bool getRunningSim() { return runningSim.load(std::memory_order_acquire); }

	/// @brief set the running state
	/// @param _running value to set
	void setRunningSim(bool _running) { runningSim.store(_running, std::memory_order_release); }

	/// @brief run the simulation synchronously for a number of ticks
	///
	/// generates 3 civs then runs the sim loop. this is the main python
	/// entry point for simple synchronous execution.
	/// @param ticks number of ticks to run
	void startSimulation(uint64_t ticks) {
		std::cout << "`startSimulation()` called!\n";
		if (!runningSim) {
			setRunningSim(true); // toggleRunningSim on
		}
		sim.Generate3Civs();
		sim.SimLoop(ticks);
		setRunningSim(false); // done so toggle running sim off
	}

	/// @brief generate 3 civilizations asynchronously
	void generate3Civs() {
		if(simThread.joinable())
			join(); // join thread if it hasn't been joined already
		simThread = std::thread([this]() {
			sim.Generate3Civs();
			});

	}

	/// @brief generate 5 civilizations asynchronously
	void generate5Civs() {
		if (simThread.joinable())
			join();
		simThread = std::thread([this]() {
			sim.Generate5Civs();
			});
	}

	/// @brief generate 10 civilizations asynchronously
	void generate10Civs() {
		if (simThread.joinable())
			join();
		simThread = std::thread([this]() {
			sim.Generate10Civs();
			});
	}

	/// @brief start the simulation asynchronously on a separate thread
	///
	/// uses an RAII guard to ensure the running flag is cleared even if
	/// the sim loop throws or exits early.
	/// @param ticks number of ticks to run
	void startSimulationAsync(uint64_t ticks) {
		if (runningSim) return;
		if(simThread.joinable())
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

	/// @brief join the sim thread if it's still running
	void join() {
		if (simThread.joinable()) {
			simThread.join();
		}
	}
};


PYBIND11_MODULE(civ_module, m, py::mod_gil_not_used()) {
	m.doc() = "Module for binding sim to python"; // Optional module docstrin
	py::class_<SimulationApi>(m, "SimulationApi")
		.def(py::init<const uint64_t, const std::string>())			// gil_scoped_release prevents blocking python so you can multithread the python script
		.def("startSimulation", &SimulationApi::startSimulation, py::call_guard<py::gil_scoped_release>(), py::arg("ticks"), "Spins up the simulation and runs for ticks")
		.def("startSimulationAsync", &SimulationApi::startSimulationAsync, py::arg("ticks"), py::call_guard<py::gil_scoped_release>())
		.def("poll_log", &SimulationApi::poll_log)
		.def("generate3Civs", &SimulationApi::generate3Civs)
		.def("generate5Civs", &SimulationApi::generate5Civs)
		.def("generate10Civs", &SimulationApi::generate10Civs)
		.def_property("runningSim", &SimulationApi::getRunningSim, &SimulationApi::setRunningSim);
}

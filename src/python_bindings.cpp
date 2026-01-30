#include <pybind11/pybind11.h>
#include "include/World.h"
#include "include/Civilization.h"
#include <Simulation.h>
#include <iostream>
#include <atomic>

namespace py = pybind11;

int add(int a = 1, int b = 2) {
	return a + b;
}

int multiply(int a = 2, int b = 2) {
	return a * b;
}

/// <summary>
/// SimulationApi is an abstraction created to create python bindings to these c++ libraries. 
/// </summary>
class SimulationApi {
private:
	Simulation sim;
	std::atomic<bool> runningSim{ false };
	std::thread simThread;
public:
	SimulationApi(uint64_t seed, std::string name) : sim(WorldSeed(seed, name)) {}
	~SimulationApi() { join(); }
	bool getRunningSim() { return runningSim.load(std::memory_order_acquire); }

	/// <summary>
	/// set the runningSim bool to the param value
	/// </summary>
	/// <param name="_running">value to set runningSim to</param>
	void setRunningSim(bool _running) { runningSim.store(_running, std::memory_order_release); }
	/// <summary>
	/// The main python entrypoint to the simulation. will be used later for logic on running the simulation x amount of ticks at a time
	/// </summary>
	/// <param name="ticks"> - the number of ticks to progress the simulation</param>
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
	///	starts the simulation for `ticks` number of ticks on a seperate thread
	/// </summary>
	/// <param name="ticks"> - the number of ticks to run the simulation for</param>
	void startSimulationAsync(uint64_t ticks) {
		if (runningSim) return;
		join();
		setRunningSim(true);

		simThread = std::thread([this, ticks]() {
			// RAII Guard
			// just a small struct with a destructor that sets the flag to false
			// that way if it goes out of scope it sets itself to false;
			struct Guard {
				std::atomic<bool>& flag;
				~Guard() { flag.store(false, std::memory_order_release); }
			} guard{runningSim};

			sim.Generate3Civs();
			sim.SimLoop(ticks);
			setRunningSim(false);
			});
	}

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
		.def_property("runningSim", &SimulationApi::getRunningSim, &SimulationApi::setRunningSim)
		.def("startSimulationAsync", &SimulationApi::startSimulationAsync, py::arg("ticks"), py::call_guard<py::gil_scoped_release>());

	m.def("add", &add, "A function that adds two numbers", py::arg("a"), py::arg("b"));
	m.def("multiply", &multiply, "A function that multiplys two numbers", py::arg("a"), py::arg("b"));
}
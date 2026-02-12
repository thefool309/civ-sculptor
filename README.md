# civ-sculptor

![GitHub License](https://img.shields.io/github/license/thefool309/civ-sculptor) ![GitHub commit activity](https://img.shields.io/github/commit-activity/w/thefool309/civ-sculptor) ![GitHub last commit](https://img.shields.io/github/last-commit/thefool309/civ-sculptor) ![GitHub Created At](https://img.shields.io/github/created-at/thefool309/civ-sculptor) ![Discord](https://img.shields.io/discord/668848824323801090) ![GitHub top language](https://img.shields.io/github/languages/top/thefool309/civ-sculptor)


Civ-Sculptor is a hybrid Python/C++ civilization simulation engine, designed for experimentation, and analysis. The simulation runs core logic in C++ for high performance and low-level control, while exposing a Python API for scripting, logging, machine learning and data visualization integration.

## Features

- **High-performance simulation core:** Written in c++ for efficient computation and multithreading

- **python bindings via pybind11:** Control simulations, inspect state, and integrate with Machine Learning workflows.

- **Asynchronous simulation execution:** Run long simulations without blocking the Python interface

- **Terminal Visualization:** Interactive real-time display using rich and textual

- **Flexible Logging:** capture and poll simulation output for analysis or UI

- **(Long Term Feature) pureSim and learning modes:** have two modes for the c++ simulation one that runs a pure random sim (pureSim) The other will be piloted by ML or RL algorithms (learning)


## Use Cases

- Generate civilizations with randomized traits.

- Run turn-based simulations to explore emergent behaviors and interactions.

- Feed simulation data into machine learning models for pattern discovery, strategy evaluation, or predictive analysis.

- Experiment with game design, AI behavior, or culture evolution in a controlled environment.

## Installation

```bash
# Build C++ library
cmake -S . -B build
cmake --build build --config Debug

# Install Python requirements
pip install -r requirements.txt
```

## Example Usage

```py
from civ_module import SimulationApi

# Create a simulation instance
sim = SimulationApi(seed=123456, name="Testonia")

# Generate civilizations
sim.generate3Civs()

# Run 10 ticks synchronously
sim.startSimulation(10)

# Run 5 ticks asynchronously
sim.startSimulationAsync(5)

# Poll log output
print(sim.poll_log())
```

## Terminal UI
Use the textual UI to interact with the simulation in real time

```bash
python src/main.py
```

## Contributing

Contributions are welcome! Open an issue or submit a pull request to improve the simulation engine, enhance the UI, or add your own examples of using this library.

## License

[Apache v2.0](https://www.apache.org/licenses/LICENSE-2.0.txt)
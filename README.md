# civ-sculptor
Civ-Sculptor is a hybrid Python/C++ civilization simulation engine, designed for experimentation, and analysis. The simulation runs core logic in C++ for high performance and low-level control, while exposing a Python API for scripting, logging, machine learning and data visualization integration.

## Installation

```
# Build C++ library
cmake -S . -B build
cmake --build build --config Debug

# Install Python requirements
pip install -r requirements.txt
```
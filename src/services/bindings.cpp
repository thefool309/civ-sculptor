#include <pybind11/pybind11.h>

namespace py = pybind11;

int add(int a, int b) {
	return a + b;
}

PYBIND11_MODULE(bindings, m) {
	m.doc() = "Example module created with pybind11"; // Optional module docstring
	m.def("add", &add, "A function that adds two numbers"), py::arg("a"), py::arg("b");

}
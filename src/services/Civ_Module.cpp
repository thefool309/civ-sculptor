#include <pybind11/pybind11.h>

namespace py = pybind11;

int add(int a = 1, int b = 2) {
	return a + b;
}

int multiply(int a = 2, int b = 2) {
	return a * b;
}

PYBIND11_MODULE(civ_module, m) {
	m.doc() = "Module for binding civilization object to python"; // Optional module docstring
	m.def("add", &add, "A function that adds two numbers"), py::arg("a"), py::arg("b");
	m.def("multiply", &multiply, "A function that multiplys two numbers"), py::arg("a"), py::arg("b");
}
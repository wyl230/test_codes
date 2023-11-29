
#include <pybind11/pybind11.h>
// #include <vector>

using namespace pybind11;

int add(int a, int b) { return a + b; }

// std::vector<int> add2(int n) {
//   std::vector<int> a = {0, 1, 2};
//   return a;
// }

// int add(int k) { return k; }

PYBIND11_MODULE(example, m) {
  m.def("add", &add, "A function which adds two numbers");
}

// PYBIND11_MODULE(add, m) {
//   m.def("add", &add, "A function which adds two numbers");
// }

// PYBIND11_MODULE(add2, m) {
//   m.def("add2", &add2, "A function which adds two numbers");
// }

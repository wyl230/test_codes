#include "memory_usage.hpp"
#include <algorithm>
#include <array>
#include <iostream>
#include <iterator>
#include <queue>
#include <string>

void test1() {
  // Construction uses aggregate initialization
  std::array<int, 3> a1{
      {1, 2, 3}}; // double-braces required in C++11 prior to
                  // the CWG 1270 revision (not needed in C++11
                  // after the revision and in C++14 and beyond)

  std::array<int, 3> a2 = {1, 2, 3}; // double braces never required after =

  std::array<std::string, 2> a3 = {std::string("E"), "\u018E"};

  // Container operations are supported
  std::sort(a1.begin(), a1.end());
  std::ranges::reverse_copy(a2, std::ostream_iterator<int>(std::cout, " "));
  std::cout << '\n';

  // Ranged for loop is supported
  for (const auto &s : a3)
    std::cout << s << ' ';

  // Deduction guide for array creation (since C++17)
  [[maybe_unused]] std::array a4{3.0, 1.0, 4.0}; // std::array<double, 3>

  // Behavior of unspecified elements is the same as with built-in arrays
  [[maybe_unused]] std::array<int, 2> a5; // no list init, a5[0] and a5[1]
                                          // are default initialized
  [[maybe_unused]] std::array<int, 2>
      a6{}; // list init, both elements are value
            // initialized, a6[0] = a6[1] = 0
  [[maybe_unused]] std::array<int, 2> a7{
      1}; // list init, unspecified element is value
          // initialized, a7[0] = 1, a7[1] = 0
}

void test2() {
  using array = std::array<int, 1024>;
  std::queue<array> q;
  int cnt = 0;
  while (true) {
    if (cnt++ % 100000 == 0) {
      std::cout << cnt << std::endl;
      print_mem(getpid(), "test");
    }

    q.push(array{1, 2, 3, 4, 5});
  }
}

int main() { test2(); }

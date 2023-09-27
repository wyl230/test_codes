
#include <array>
#include <iostream>
#include <queue>
#include <sltbench/BenchCore.h>

#include <memory>
#include <string>

using test_array = std::array<char, 655360>;
using unique_test_array = std::unique_ptr<test_array>;

void value_queue_ptr2value() {
  std::queue<test_array> q;
  for (size_t i = 0; i < 1000; ++i) {
    unique_test_array test = std::make_unique<test_array>();
    for (auto &c : *test) {
      c = 'a';
    }
    q.push(std::move(*test));
  }
}
SLTBENCH_FUNCTION(value_queue_ptr2value);

void ptr_queue_new_ptr() {
  std::queue<unique_test_array> q;
  for (size_t i = 0; i < 1000; ++i) {
    unique_test_array test = std::make_unique<test_array>();
    for (auto &c : *test) {
      c = 'a';
    }
    q.push(std::move(test));
  }
}
SLTBENCH_FUNCTION(ptr_queue_new_ptr);

void ptr_queue_value_make_ptr() {
  std::queue<unique_test_array> q;
  for (size_t i = 0; i < 1000; ++i) {
    test_array test;
    for (auto &c : test) {
      c = 'a';
    }
    q.push(std::make_unique<test_array>());
  }
}
SLTBENCH_FUNCTION(ptr_queue_value_make_ptr);

void value_queue_value() {
  std::queue<test_array> q;
  for (size_t i = 0; i < 1000; ++i) {
    test_array test;
    for (auto &c : test) {
      c = 'a';
    }
    q.push(test);
  }
}
SLTBENCH_FUNCTION(value_queue_value);

void usecopy() {
  std::queue<test_array> q;

  test_array test;
  for (auto &c : test) {
    c = 'a';
  }
  for (size_t i = 0; i < 1000; ++i) {
    test_array in_test;
    std::copy(test.begin(), test.end(), in_test.begin());
    q.push(test);
  }
}
SLTBENCH_FUNCTION(usecopy);

void usecopy2() {
  std::queue<unique_test_array> q;

  test_array test;
  for (auto &c : test) {
    c = 'a';
  }

  for (size_t i = 0; i < 1000; ++i) {
    unique_test_array in_test = std::make_unique<test_array>(test);
    q.push(std::move(in_test));
  }
}
SLTBENCH_FUNCTION(usecopy2);

// void pre_value_queue_value() {
//   std::queue<test_array> q;
//   test_array test;
//   for (auto &c : test) {
//     c = 'a';
//   }
//
//   for (size_t i = 0; i < 1000; ++i) {
//     q.push(test);
//   }
// }
// SLTBENCH_FUNCTION(pre_value_queue_value);

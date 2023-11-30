#pragma once
#include <coroutine>
#include <iostream>
struct promise_test {
  struct promise_type {
    promise_test get_return_object() {
      std::cout << "get_return_object" << std::endl;
      return {};
    }
    std::suspend_never initial_suspend() {
      std::cout << "initial_suspend" << std::endl;
      return {};
    }
    std::suspend_never final_suspend() noexcept {
      std::cout << "final_suspend" << std::endl;
      return {};
    }
    void return_void() { std::cout << "return_void" << std::endl; }
    void unhandled_exception() {
      std::cout << "unhandled_exception" << std::endl;
    }
  };
};
inline promise_test test_coroutine() {
  std::cout << "create coroutine" << std::endl;
  co_return;
}

inline void test_coroutine_main() {
  std::cout << "=========================" << std::endl;
  std::cout << "start test_coroutine_main" << std::endl;
  std::cout << "-------------------------" << std::endl;
  promise_test x = test_coroutine();
  std::cout << "-----------------------" << std::endl;
  std::cout << "end test_coroutine_main" << std::endl;
  std::cout << "=======================" << std::endl;
}

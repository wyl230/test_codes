
#pragma once
#include <coroutine>
#include <iostream>
namespace test_co_yield {
struct generator_int {
  struct promise_type {
    int value;

    generator_int get_return_object() {
      return generator_int{
          std::coroutine_handle<promise_type>::from_promise(*this)};
    }
    std::suspend_always initial_suspend() noexcept { return {}; }
    std::suspend_always final_suspend() noexcept { return {}; }
    void unhandled_exception() { throw std::current_exception(); }
    void return_void() {}

    std::suspend_always yield_value(int v) {
      std::cout << "yield_value: " << v << std::endl;
      value = v;
      return {};
    }
  };

  int next() {
    handle.resume();
    return handle.promise().value;
  }

  std::coroutine_handle<promise_type> handle;
};

inline generator_int get_number() {
  int i = 1;
  while (true) {
    co_yield i++;
  }
}

inline void test_co_yield() {
  auto num = get_number();
  for (int j = 0; j < 10; ++j) {
    std::cout << num.next() << std::endl;
  }
}
} // namespace test_co_yield

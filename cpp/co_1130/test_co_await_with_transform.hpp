#include <coroutine>
#include <iostream>
#include <print.hpp>
using namespace std;

namespace test_co_await_with_transform {
template <typename T> struct MyAwaitable {
  T value;

  bool await_ready() const noexcept {
    // Check if the value is ready to be awaited
    // For simplicity, always return true in this example
    print(__func__);
    return true;
  }

  void await_suspend(std::coroutine_handle<> coro) const {
    print(__func__);
    // Suspend the coroutine and store the coroutine handle for later resumption
    // For simplicity, do nothing in this example
  }

  T await_resume() const noexcept {
    print(__func__);
    // Return the result of the asynchronous operation
    return value;
  }
};

struct promise_test {
  struct promise_type;
  std::coroutine_handle<promise_type> m_handle;
  promise_test(std::coroutine_handle<promise_type> handle) : m_handle(handle) {}
  ~promise_test() { m_handle.destroy(); }

  struct promise_type {
    auto get_return_object() {
      return promise_test{
          std::coroutine_handle<promise_type>::from_promise(*this)};
    }
    auto initial_suspend() { return std::suspend_never{}; }
    auto final_suspend() noexcept { return std::suspend_always{}; }
    void return_void() {}
    void unhandled_exception() { std::terminate(); }
    MyAwaitable<int> await_transform(int value) {
      // This function is called when co_await is used with an integer
      // You can return an object that satisfies the awaitable concept
      print(__func__, __LINE__, ": value: ", value);
      return MyAwaitable<int>{value};
    }
  };

  bool resume() {
    if (!m_handle.done())
      m_handle.resume();
    return !m_handle.done();
  }
};

inline promise_test func() {
  std::cout << __func__ << ": Starting coroutine" << std::endl;
  for (int i = 0; i < 6; ++i) {
    auto a = co_await i * i;
    print("this is a: ", a);
    std::cout << __func__ << ": Resuming coroutine" << std::endl;
  }
}

inline void test_co_await() {
  std::cout << "==================" << std::endl;
  std::cout << "test_co_await start" << std::endl;
  std::cout << "------------------" << std::endl;
  auto gen = func();
  std::cout << __func__ << ": Yielding coroutine" << std::endl;
  bool not_done;
  not_done = gen.resume();
  print("is done? ", !not_done);
  not_done = gen.resume();
  print("is done? ", !not_done);
  not_done = gen.resume();
  print("is done? ", !not_done);
  not_done = gen.resume();
  print("is done? ", !not_done);
  std::cout << __func__ << ": Finished" << std::endl;
  std::cout << "------------------" << std::endl;
  std::cout << "test_co_await end" << std::endl;
  std::cout << "==================" << std::endl;
}
} // namespace test_co_await_with_transform

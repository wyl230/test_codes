#include <coroutine>
#include <iostream>
#include <print.hpp>
using namespace std;

namespace test_co_await {
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
  };

  bool resume() {
    if (!m_handle.done())
      m_handle.resume();
    return !m_handle.done();
  }
};

inline promise_test func() {
  std::cout << __func__ << ": Starting coroutine" << std::endl;
  co_await std::suspend_always{};
  std::cout << __func__ << ": Resuming coroutine" << std::endl;
  co_await std::suspend_always{};
  print(__func__, __LINE__, ": Resuming coroutine");
  co_await std::suspend_always{};
  print(__func__, __LINE__, ": Resuming coroutine");
  co_await std::suspend_always{};
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
} // namespace test_co_await

#include <coroutine>
#include <iostream>
#include <memory>
#include <print.hpp>

namespace test_co_return_with_return_value {
struct generator_int {
  struct promise_type;
  std::coroutine_handle<promise_type> m_handle;
  generator_int(std::coroutine_handle<promise_type> handle)
      : m_handle(handle) {}
  ~generator_int() { m_handle.destroy(); }
  int get() {
    if (m_handle && !m_handle.done())
      m_handle.resume();
    return m_handle.promise().value;
  }
  struct promise_type {
    int value = {};
    promise_type() {}
    ~promise_type() {}
    auto get_return_object() {
      return generator_int{
          std::coroutine_handle<promise_type>::from_promise(*this)};
    }
    void return_value(int v) { // 对应 co_return的值做处理
      print("return value: ", v);
      value = v;
    }
    auto initial_suspend() { return std::suspend_always{}; }
    auto final_suspend() noexcept { return std::suspend_always{}; }
    void unhandled_exception() { std::exit(1); }
  };
  bool isDone() const {
    print("Checking if task is done...\n");
    return !m_handle || m_handle.done();
  }
};

inline generator_int task() { co_return 100; }

inline void test_co_return() {
  auto fut = task();
  auto done = fut.isDone();
  print("Is task done? ", done);
  // while (!fut.isDone()) {
  //   print("wait");
  // }
  std::cout << "fut.get(): " << fut.get() << '\n';
  print("Is task done? ", fut.isDone());
  std::cout << "fut.get(): " << fut.get() << '\n';
  print("Is task done? ", fut.isDone());
  std::cout << "fut.get(): " << fut.get() << '\n';
  print("Is task done? ", fut.isDone());
}
} // namespace test_co_return_with_return_value

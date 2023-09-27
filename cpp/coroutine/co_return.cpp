#include <coroutine>
#include <future>
#include <iostream>
#include <string>

using namespace std;

template <typename T> struct lazy {
  struct promise_type;
  using handle = std::coroutine_handle<promise_type>;
  struct promise_type {
    T _return_value;
    static auto get_return_object_on_allocation_failure() {
      return lazy{nullptr};
    }
    auto get_return_object() { return lazy{handle::from_promise(*this)}; }
    auto initial_suspend() { return std::suspend_always{}; }
    auto final_suspend() { return std::suspend_always{}; }
    void unhandled_exception() { std::terminate(); }
    void return_value(T value) { _return_value = value; }
  };
  bool calculate() {
    if (calculated)
      return true;
    if (!coro)
      return false;
    coro.resume();
    if (coro.done())
      calculated = true;
    return calculated;
  }
  T get() { return coro.promise()._return_value; }
  lazy(lazy const &) = delete;
  lazy(lazy &&rhs) : coro(rhs.coro) { rhs.coro = nullptr; }
  ~lazy() {
    if (coro)
      coro.destroy();
  }

private:
  lazy(handle h) : coro(h) {}
  handle coro;
  bool calculated{false};
};

lazy<std::string> f(std::string n = "qwer") { co_return n + "asdf"; }

int main() {
  auto g = f();
  g.calculate(); // 这时才从 initial_suspend 之中恢复, 所以就叫 lazy 了
  cout << g.get();
}

#include <coroutine>
#include <iostream>

template <typename T> struct generator {
  struct promise_type;
  using handle = std::coroutine_handle<promise_type>;
  struct promise_type {
    T current_value;
    static auto get_return_object_on_allocation_failure() {
      return generator{nullptr};
    }
    auto get_return_object() { return generator{handle::from_promise(*this)}; }
    auto initial_suspend() { return std::suspend_always{}; }
    auto final_suspend() { return std::suspend_always{}; }
    void unhandled_exception() { std::terminate(); }
    void return_void() {}
    auto yield_value(T value) {
      current_value = value;
      return std::suspend_always{};
    }
  };
  bool move_next() { return coro ? (coro.resume(), !coro.done()) : false; }
  T current_value() { return coro.promise().current_value; }
  generator(generator const &) = delete;
  generator(generator &&rhs) : coro(rhs.coro) { rhs.coro = nullptr; }
  ~generator() {
    if (coro)
      coro.destroy();
  }

private:
  generator(handle h) : coro(h) {}
  handle coro;
};

generator<int> f() {
  co_yield 1;
  co_yield 2;
}

generator<std::string> ff() {
  co_yield "234234";
  co_yield "qwer";
}

int main() {
  auto g = ff();
  while (g.move_next())
    std::cout << g.current_value() << std::endl;
}

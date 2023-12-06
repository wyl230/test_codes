#include <coroutine>
#include <iostream>
#include <print.hpp>
namespace simple_example {

size_t level = 0;
std::string INDENT = "> ";

class Trace {
public:
  Trace() { in_level(); }
  ~Trace() { level -= 1; }
  void in_level() {
    level += 1;
    std::string res(INDENT);
    for (size_t i = 0; i < level; i++) {
      res.append(INDENT);
    };
    // res += " ";
    std::cout << res;
  }
};

template <typename T> struct sync {
  struct promise_type;
  using handle_type = std::coroutine_handle<promise_type>;
  handle_type coro;

  sync(handle_type h) : coro(h) {
    Trace t;
    std::cout << "Created a sync object" << std::endl;
  }
  sync(const sync &) = delete;
  sync(sync &&s) : coro(s.coro) {
    Trace t;
    std::cout << "Sync moved leaving behind a husk" << std::endl;
    s.coro = nullptr;
  }
  ~sync() {
    Trace t;
    std::cout << "Sync gone" << std::endl;
    if (coro)
      coro.destroy();
  }
  sync &operator=(const sync &) = delete;
  sync &operator=(sync &&s) {
    coro = s.coro;
    s.coro = nullptr;
    return *this;
  }

  T get() {
    Trace t;
    std::cout << "We got asked for the return value..." << std::endl;
    return coro.promise().value;
  }
  struct promise_type {
    T value;
    promise_type() {
      Trace t;
      std::cout << "Promise created" << std::endl;
    }
    ~promise_type() {
      Trace t;
      std::cout << "Promise died" << std::endl;
    }

    auto get_return_object() {
      Trace t;
      std::cout << "Send back a sync" << std::endl;
      return sync<T>{handle_type::from_promise(*this)};
    }
    auto initial_suspend() {
      Trace t;
      std::cout << "Started the coroutine, don't stop now!" << std::endl;
      return std::suspend_never{};
      // std::cout << "--->Started the coroutine, put the brakes on!" <<
      // std::endl; return std::suspend_always{};
    }
    auto return_value(T v) {
      Trace t;
      std::cout << "(sync)Got an answer of " << v << std::endl;
      value = v;
      return std::suspend_never{};
    }
    auto final_suspend() noexcept {
      Trace t;
      std::cout << "Finished the coro" << std::endl;
      return std::suspend_always{};
    }
    void unhandled_exception() { std::exit(1); }
  };
};

template <typename T> struct lazy {
  struct promise_type;
  using handle_type = std::coroutine_handle<promise_type>;
  handle_type coro;

  lazy(handle_type h) : coro(h) {
    Trace t;
    std::cout << "Created a lazy object" << std::endl;
  }
  lazy(const lazy &) = delete;
  lazy(lazy &&s) : coro(s.coro) {
    Trace t;
    std::cout << "lazy moved leaving behind a husk" << std::endl;
    s.coro = nullptr;
  }
  ~lazy() {
    Trace t;
    std::cout << "lazy gone" << std::endl;
    if (coro)
      coro.destroy();
  }
  lazy &operator=(const lazy &) = delete;
  lazy &operator=(lazy &&s) {
    coro = s.coro;
    s.coro = nullptr;
    return *this;
  }

  T get() {
    Trace t;
    std::cout << "We got asked for the return value..." << std::endl;
    return coro.promise().value;
  }
  struct promise_type {
    T value;
    promise_type() {
      Trace t;
      std::cout << "Promise created" << std::endl;
    }
    ~promise_type() {
      Trace t;
      std::cout << "Promise died" << std::endl;
    }

    auto get_return_object() {
      Trace t;
      std::cout << "Send back a lazy" << std::endl;
      return lazy<T>{handle_type::from_promise(*this)};
    }
    auto initial_suspend() {
      Trace t;
      // std::cout << "Started the coroutine, don't stop now!" << std::endl;
      // return std::suspend_never{};
      std::cout << "Started the coroutine, put the brakes on!" << std::endl;
      return std::suspend_always{};
    }
    auto return_value(T v) {
      Trace t;
      std::cout << "(lazy)Got an answer of " << v << std::endl;
      value = v;
      return std::suspend_never{};
    }
    auto final_suspend() noexcept {
      Trace t;
      std::cout << "Finished the coro" << std::endl;
      return std::suspend_always{};
    }
    void unhandled_exception() { std::exit(1); }
  };
  bool await_ready() {
    const auto ready = this->coro.done();
    Trace t;
    std::cout << "Await " << (ready ? "is ready" : "isn't ready") << std::endl;
    return this->coro.done();
  }
  void await_suspend(std::coroutine_handle<> awaiting) {
    {
      Trace t;
      std::cout << "About to resume the lazy" << std::endl;
      this->coro.resume();
    }
    Trace t;
    std::cout << "About to resume the awaiter" << std::endl;
    awaiting.resume();
  }
  T await_resume() {
    const T r = this->coro.promise().value;
    Trace t;
    std::cout << "Await value is returned: " << r << std::endl;
    return r;
  }
};

inline lazy<std::string> read_data() {
  Trace t;
  std::cout << "Reading data..." << std::endl;
  co_return "billion$!";
}

inline lazy<std::string> write_data() {
  Trace t;
  std::cout << "Write data..." << std::endl;
  co_return "I'm rich!";
}
inline sync<int> reply() {
  std::cout << "Started await_answer" << std::endl;
  auto a = co_await read_data();
  std::cout << "Data we got is " << a << std::endl;
  auto v = co_await write_data();
  std::cout << "write result is " << v << std::endl;
  co_return 42;
}

inline sync<int> reply_multi() {
  for (int i = 0; i < 10; ++i) {
    std::cout << "Started await_answer" << std::endl;
    auto a = co_await read_data();
    std::cout << "Data we got is " << a << std::endl;
    auto v = co_await write_data();
    std::cout << "write result is " << v << std::endl;
  }
  co_return 42;
}

inline void run_example() {
  std::cout << "Start main()\n";
  auto a = reply();
  auto b = reply_multi();
  print("we get a:", a.get());
}
} // namespace simple_example

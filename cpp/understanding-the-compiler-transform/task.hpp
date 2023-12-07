#include <chrono>
#include <coroutine>
#include <iostream>
#include <print.hpp>
#include <thread>
#include <variant>

// 基本task类型，它既充当可等待类型又充当协程返回类型
class task {
public:
  struct awaiter;

  class promise_type {
  public:
    promise_type() noexcept;
    ~promise_type();

    struct final_awaiter {
      bool await_ready() noexcept;
      std::coroutine_handle<>
      await_suspend(std::coroutine_handle<promise_type> h) noexcept;
      void await_resume() noexcept;
    };

    task get_return_object() noexcept;
    std::suspend_always initial_suspend() noexcept;
    final_awaiter final_suspend() noexcept;
    void unhandled_exception() noexcept;
    void return_value(int result) noexcept;

  private:
    friend task::awaiter;
    std::coroutine_handle<> continuation_;

  public:
    std::variant<std::monostate, int, std::exception_ptr> result_;
  };

  task(task &&t) noexcept;
  ~task();
  task &operator=(task &&t) noexcept;

  struct awaiter {
    explicit awaiter(std::coroutine_handle<promise_type> h) noexcept;
    bool await_ready() noexcept;
    std::coroutine_handle<promise_type>
    await_suspend(std::coroutine_handle<> h) noexcept;
    int await_resume();

  private:
    std::coroutine_handle<promise_type> coro_;
  };

  awaiter operator co_await() && noexcept;
  int get() {
    print("get");
    if (coro_ && !coro_.done()) {
      print("get then resume");
      coro_.resume();
      print("get then resume2");
    }
    print("get2");
    // return coro_.promise().result_.get<int>();
    // return coro_.promise().result_.index();

    if (std::holds_alternative<int>(coro_.promise().result_)) {
      return std::get<int>(coro_.promise().result_);
    } else {
      // 处理不是int类型的情况，这里可以抛出异常或者返回一个默认值
      // 在这个例子中，返回一个特殊值 -1 作为默认值
      return -1;
    }
  }

  bool resume() {
    if (coro_ && !coro_.done()) {
      coro_.resume();
      return true;
    }
    return false;
  }

private:
  explicit task(std::coroutine_handle<promise_type> h) noexcept;

  std::coroutine_handle<promise_type> coro_;
};

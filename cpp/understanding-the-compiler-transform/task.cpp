#include "task.hpp"
#include <exception>
// task.cpp

task::promise_type::promise_type() noexcept : result_() {}

task::promise_type::~promise_type() {}

bool task::promise_type::final_awaiter::await_ready() noexcept { return false; }

std::coroutine_handle<> task::promise_type::final_awaiter::await_suspend(
    std::coroutine_handle<promise_type> h) noexcept {
  return h.promise().continuation_;
}

void task::promise_type::final_awaiter::await_resume() noexcept {}

task task::promise_type::get_return_object() noexcept {
  return task{std::coroutine_handle<promise_type>::from_promise(*this)};
}

std::suspend_always task::promise_type::initial_suspend() noexcept {
  return {};
}

task::promise_type::final_awaiter task::promise_type::final_suspend() noexcept {
  return {};
}

void task::promise_type::unhandled_exception() noexcept {
  result_ = std::current_exception();
}

void task::promise_type::return_value(int result) noexcept {
  result_ = result;
  print("set_return value");
}

task::task(std::coroutine_handle<promise_type> h) noexcept : coro_(h) {}

task::task(task &&t) noexcept : coro_(t.coro_) { t.coro_ = nullptr; }

task::~task() {
  if (coro_)
    coro_.destroy();
}

task &task::operator=(task &&t) noexcept {
  if (this != &t) {
    if (coro_)
      coro_.destroy();
    coro_ = t.coro_;
    t.coro_ = nullptr;
  }
  return *this;
}

task::awaiter::awaiter(std::coroutine_handle<promise_type> h) noexcept
    : coro_(h) {}

bool task::awaiter::await_ready() noexcept { return false; }

std::coroutine_handle<task::promise_type>
task::awaiter::await_suspend(std::coroutine_handle<> h) noexcept {
  coro_.promise().continuation_ = h;
  return coro_;
}

int task::awaiter::await_resume() {
  auto &result = coro_.promise().result_;
  print(__func__, ": await_resume");
  if (result.index() == 1) {
    print(__func__, ": result = ", std::get<1>(result));
    return std::get<1>(result);
  } else {
    print(__func__, ": result");
    std::rethrow_exception(std::get<2>(result));
  }
}

task::awaiter task::operator co_await() && noexcept { return awaiter{coro_}; }


/*
 * co_vs_callback.cpp
 *
 *  Created on: Mar 13, 2019
 *      Author: frank
 */
#include <better_print.hpp>
#include <chrono>
#include <coroutine>
#include <functional>
#include <iostream>
#include <thread>

// clang++ -std=c++2a -fcoroutines-ts -lstdc++ co_vs_callback.cpp

using call_back = std::function<void(int)>;
void Add100ByCallback(int init, call_back f) // 异步调用
{
  std::thread t([init, f]() {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    f(init + 100);
  });
  t.detach();
}

struct Add100AWaitable {
  Add100AWaitable(int init) : init_(init) {}
  bool await_ready() const { return false; }
  int await_resume() { return result_; }
  void await_suspend(std::coroutine_handle<> handle) {
    auto f = [handle, this](int value) mutable {
      result_ = value;
      handle.resume();
    };
    Add100ByCallback(init_, f); // 调用原来的异步调用
  }
  int init_;
  int result_;
};

struct Task {
  struct promise_type {
    auto get_return_object() { return Task{}; }
    auto initial_suspend() { return std::suspend_never{}; }
    auto final_suspend() { return std::suspend_never{}; }
    void unhandled_exception() { std::terminate(); }
    void return_void() {}
  };
};

Task Add100ByCoroutine(int init, call_back f) {
  int ret = co_await Add100AWaitable(init);
  f(ret);
  ret = co_await Add100AWaitable(ret);
  f(ret);
  ret = co_await Add100AWaitable(ret);
  f(ret);
}

int main() {
  Add100ByCallback(
      5, [](int value) { std::cout << "get result: " << value << "\n"; });

  print("emm");

  Add100ByCoroutine(10, [](int value) {
    std::cout << "get result from coroutine1: " << value << "\n";
  });
  print("eme1m");

  Add100ByCoroutine(20, [](int value) {
    std::cout << "get result from coroutine2: " << value << "\n";
  });
  print("eme2m");

  Add100ByCoroutine(30, [](int value) {
    std::cout << "get result from coroutine3: " << value << "\n";
  });
  print("eme3m");

  Add100ByCoroutine(40, [](int value) {
    std::cout << "get result from coroutine4: " << value << "\n";
  });

  print("eme4m");
  while (true)
    ;
}

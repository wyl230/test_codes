// TODO:
#include <chrono>
#include <coroutine>
#include <iostream>
#include <print.hpp>
#include <thread>

namespace async_with_coroutine {

// 异步任务的可等待对象
struct AsyncTask {
  mutable bool is_ready = false;

  bool await_ready() const noexcept {
    // is_ready = true;
    print("Async task is ready...? ", is_ready ? "ready" : "not ready");
    return is_ready; // 任务是否已完成
  }

  void await_suspend(std::coroutine_handle<> coroHandle) const {
    // 模拟异步操作，例如在另一个线程中执行
    print("Async task is suspended...");
    std::thread([coroHandle]() {
      print("Async task is running...");
      std::this_thread::sleep_for(std::chrono::seconds(1));
      std::cout << "Async task is done!\n";
      coroHandle.resume(); // 恢复协程的执行
    }).detach();
  }

  void await_resume() const noexcept {
    // 异步操作完成后的处理
    std::cout << "Async task resumed...\n";
  }
};

// 协程
struct MyCoroutine {
  struct promise_type;
  std::coroutine_handle<promise_type> m_handle;
  MyCoroutine(std::coroutine_handle<promise_type> handle) : m_handle(handle) {}
  ~MyCoroutine() {
    // gm_handle.destroy();
    if (m_handle) {
      if (!m_handle.done()) {
        m_handle.destroy();
      } else {
        print("m_handle is done");
      }
    }
  }
  struct promise_type {
    // MyCoroutine get_return_object() {
    //   return {}; // 创建协程对象
    // }

    auto get_return_object() {
      return MyCoroutine{
          std::coroutine_handle<promise_type>::from_promise(*this)};
    }

    std::suspend_never initial_suspend() const noexcept {
      return {}; // 协程开始时不挂起
    }

    std::suspend_never final_suspend() const noexcept {
      return {}; // 协程结束时不挂起
    }

    void return_void() const noexcept {}
    void unhandled_exception() { std::terminate(); }
  };

  AsyncTask operator co_await() const {
    return {}; // 返回一个异步任务的可等待对象
  }
  bool resume() {
    print("=======================");
    print("Coroutine is resumed...");
    if (!m_handle.done()) {
      print("Coroutine is not done...");
      m_handle.resume();
    }
    print("return resume\n");
    print("=============\n");
    return !m_handle.done();
  }
};

// 使用协程执行异步任务
inline MyCoroutine asyncTask() {
  std::cout << "Start async task...\n";
  co_await AsyncTask{}; // 使用 co_await 挂起协程，等待异步任务完成
  std::cout << "Async task completed!\n";
}

inline void example() {
  MyCoroutine coro = asyncTask();
  // coro.resume();
  // print("emm");
  // print("is done? ", !coro.resume());
  // print("is done? ", !coro.resume());
  // print("is done? ", !coro.resume());
  // 在实际应用中，可能需要通过事件循环等方式来处理协程的执行
  // 这里为了演示，简单地等待协程完成

  print("Main continues...");
  for (int i = 0; i < 12; ++i) {
    print("i = ", i);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
}
} // namespace async_with_coroutine

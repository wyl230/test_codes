#include <chrono>
#include <coroutine>
#include <future>
#include <iostream>
#include <print.hpp>
#include <string>
#include <thread>

using namespace std;

// lazy 是 协程的返回值类型
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

  bool resume() {
    print("Coroutine is resumed...\n");
    if (!coro.done()) {
      print("Coroutine is not done...\n");
      coro.resume();
    }
    print("return resume\n");
    return !coro.done();
  }

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

lazy<int> calculate_sum() {
  co_await std::suspend_always{};
  co_return 1 + 2 + 3;
}

void basic_test() {
  lazy<int> result = calculate_sum();
  // result.resume();
  // result.resume();
  while (!result.calculate())
    ;
  std::cout << "Result: " << result.get() << std::endl; // 执行实际的计算
}

lazy<int> async_task() {
  std::cout << "Task started..." << std::endl;
  co_await std::suspend_always{};
  std::this_thread::sleep_for(std::chrono::seconds(1)); // 模拟异步操作
  std::cout << "Task completed." << std::endl;
  co_return 42;
}

void async_task_test() {
  lazy<int> result = async_task();
  std::cout << "Waiting for task to complete..." << std::endl;
  while (!result.calculate())
    ;
  // std::this_thread::sleep_for(
  //     std::chrono::seconds(1)); // 在此期间任务并未真正开始
  std::cout << "Result: " << result.get() << std::endl; // 开始并等待任务完成
}

lazy<int> lazy_calculation() {
  std::cout << "Performing lazy calculation..." << std::endl;
  co_await std::suspend_always{};
  co_return 7 * 6 * 3;
}

void lazy_calculation_test() {
  lazy<int> result = lazy_calculation();

  // 在此处执行其他操作，直到需要获取结果时才进行实际计算
  std::cout << "Some other work..." << std::endl;
  while (!result.calculate())
    ;

  std::cout << "Lazy Result: " << result.get() << std::endl; // 执行实际的计算
}

int main() {
  print("==========");
  print("basic_test");
  print("----------");
  basic_test();
  print("==========");
  print("async_task_test");
  print("----------");
  async_task_test();
  print("==========");
  print("lazy_calculation_test");
  print("----------");
  lazy_calculation_test();
  // auto g = f();
  // g.calculate(); // 这时才从 initial_suspend 之中恢复, 所以就叫 lazy 了
  // cout << g.get();
}

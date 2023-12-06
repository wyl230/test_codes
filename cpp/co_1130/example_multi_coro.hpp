#include <chrono>
#include <coroutine>
#include <iostream>
#include <thread>
#include <vector>

namespace multi_coroutine {
class DisplayCoroutine {
public:
  DisplayCoroutine(int num) : num(num) {}
  DisplayCoroutine() {}

  struct promise_type;
  using handle_type = std::coroutine_handle<promise_type>;
  handle_type coro;

  struct promise_type {
    DisplayCoroutine get_return_object() { return DisplayCoroutine{}; }
    std::suspend_always initial_suspend() { return {}; }
    std::suspend_always final_suspend() noexcept { return {}; }
    void return_void() {}
    void unhandled_exception() {}
  };

  bool await_ready() const noexcept {
    const auto ready = this->coro.done();
    std::cout << "Await " << (ready ? "is ready" : "isn't ready") << std::endl;
    return this->coro.done();
  }

  void await_suspend(std::coroutine_handle<> handle) const {
    std::chrono::seconds duration(1);
    std::this_thread::sleep_for(duration);
    std::cout << num << std::endl;
    handle.resume();
  }

  void await_resume() const noexcept {}

private:
  int num;
};

void test() {
  std::vector<DisplayCoroutine> coroutineHandles;

  for (int num = 0; num < 10; ++num) {
    coroutineHandles.push_back(DisplayCoroutine(num));
  }

  for (auto &coroutine : coroutineHandles) {
    // std::coroutine_handle<DisplayCoroutine::promise_type> handle = coroutine;
    // handle.resume();
  }
  std::this_thread::sleep_for(std::chrono::seconds(2));
}
} // namespace multi_coroutine

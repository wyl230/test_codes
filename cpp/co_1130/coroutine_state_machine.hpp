// to be done
#include <chrono>
#include <coroutine>
#include <iostream>
#include <thread>

// 异步任务的状态
enum class TaskState { Init, Processing, Completed, Failed };

// 异步任务的结果
struct TaskResult {
  bool success;
  std::string message;
};

// 异步任务的协程状态机
class AsyncTaskStateMachine {
public:
  struct promise_type;

  class Handle {
  public:
    using coroutine_handle_t = std::coroutine_handle<promise_type>;

    explicit Handle(coroutine_handle_t coroutine) : coroutine_(coroutine) {}

    ~Handle() {
      if (coroutine_)
        coroutine_.destroy();
    }

    Handle(const Handle &) = delete;
    Handle &operator=(const Handle &) = delete;

    Handle(Handle &&other) noexcept : coroutine_(other.coroutine_) {
      other.coroutine_ = nullptr;
    }

    Handle &operator=(Handle &&other) noexcept {
      if (this != &other) {
        if (coroutine_)
          coroutine_.destroy();
        coroutine_ = other.coroutine_;
        other.coroutine_ = nullptr;
      }
      return *this;
    }

    bool await_ready() const noexcept {
      return coroutine_.awaitingCoroutine_ &&
             !coroutine_.awaitingCoroutine_.done();
    }

    void await_suspend(std::coroutine_handle<> awaitingCoroutine) noexcept {
      coroutine_.awaitingCoroutine_ = awaitingCoroutine;
    }

    void await_resume() const noexcept {}

    TaskState state() const { return coroutine_.state_; }

    TaskResult result() const { return coroutine_.result_; }

    void resume() {
      if (coroutine_)
        coroutine_.resume();
    }

  private:
    coroutine_handle_t coroutine_;
  };

  struct promise_type {
    TaskState state_ = TaskState::Init;
    TaskResult result_;
    std::coroutine_handle<> awaitingCoroutine_;

    auto get_return_object() {
      return AsyncTaskStateMachine::Handle{
          coroutine_handle_type::from_promise(*this)};
    }

    auto initial_suspend() { return std::suspend_never{}; }

    auto final_suspend() noexcept { return std::suspend_always{}; }

    void unhandled_exception() {
      result_ = {false, "Exception occurred."};
      state_ = TaskState::Failed;
    }

    void return_void() {}

    auto await_transform(std::coroutine_handle<> awaitingCoroutine) {
      awaitingCoroutine_ = awaitingCoroutine;
      return AsyncTaskStateMachine::Handle{
          coroutine_handle_type::from_promise(*this)};
    }
  };

private:
  using coroutine_handle_type = std::coroutine_handle<promise_type>;

public:
  explicit AsyncTaskStateMachine(coroutine_handle_type coroutine)
      : coroutine_(coroutine) {}

  ~AsyncTaskStateMachine() {
    if (coroutine_)
      coroutine_.destroy();
  }

  AsyncTaskStateMachine(const AsyncTaskStateMachine &) = delete;
  AsyncTaskStateMachine &operator=(const AsyncTaskStateMachine &) = delete;

  AsyncTaskStateMachine(AsyncTaskStateMachine &&other) noexcept
      : coroutine_(other.coroutine_) {
    other.coroutine_ = nullptr;
  }

  AsyncTaskStateMachine &operator=(AsyncTaskStateMachine &&other) noexcept {
    if (this != &other) {
      if (coroutine_)
        coroutine_.destroy();
      coroutine_ = other.coroutine_;
      other.coroutine_ = nullptr;
    }
    return *this;
  }

  void start() {
    if (coroutine_)
      coroutine_.resume();
  }

  bool isCompleted() const { return coroutine_.done(); }

private:
  coroutine_handle_type coroutine_;
};

// 模拟异步任务
TaskResult simulateAsyncTask() {
  std::cout << "Async task started..." << std::endl;
  std::this_thread::sleep_for(std::chrono::seconds(2));

  // 模拟任务成功完成
  return {true, "Async task completed successfully."};
}

// 异步任务的协程
AsyncTaskStateMachine::Handle asyncTaskCoroutine() {
  co_await std::suspend_always{}; // 初始暂停

  std::cout << "Async task coroutine started..." << std::endl;

  // 执行异步任务
  TaskResult result = simulateAsyncTask();

  co_await std::suspend_always{}; // 最终暂停

  co_return result;
}

int main() {
  AsyncTaskStateMachine asyncTask(asyncTaskCoroutine());

  std::cout << "Main coroutine started..." << std::endl;

  asyncTask.start(); // 启动异步任务

  // 在主协程中等待异步任务完成
  while (!asyncTask.isCompleted()) {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }

  std::cout << "Async task completed. Result: ";
  if (asyncTask.result().success) {
    std::cout << "Success: " << asyncTask.result().message << std::endl;
  } else {
    std::cout << "Failure: " << asyncTask.result().message << std::endl;
  }

  std::cout << "Main coroutine finished." << std::endl;

  return 0;
}


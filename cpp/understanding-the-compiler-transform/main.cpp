#include <coroutine>
#include <iostream>
#include <print.hpp>

template <typename T> class Task {
public:
  struct promise_type;
  using CoroutineHandle = std::coroutine_handle<promise_type>;

  Task(CoroutineHandle handle) : coroutineHandle(handle) {}

  ~Task() {
    if (coroutineHandle)
      coroutineHandle.destroy();
  }

  // Task(const Task &) = delete;
  // Task &operator=(const Task &) = delete;
  //
  // Task(Task &&other) noexcept : coroutineHandle(other.coroutineHandle) {
  //   other.coroutineHandle = nullptr;
  // }
  //
  // Task &operator=(Task &&other) noexcept {
  //   if (this != &other) {
  //     if (coroutineHandle)
  //       coroutineHandle.destroy();
  //
  //     coroutineHandle = other.coroutineHandle;
  //     other.coroutineHandle = nullptr;
  //   }
  //   return *this;
  // }

  T getValue() { return coroutineHandle.promise().value; }

  bool isDone() const {

    print("Checking if task is done...\n");
    // if (coroutineHandle.done()) {
    //   print("---\n");
    // }
    print("...\n");

    return !coroutineHandle;
    return !coroutineHandle || coroutineHandle.done();
  }

  void resume() const {
    if (coroutineHandle)
      coroutineHandle.resume();
  }

  struct promise_type {
    T value;

    auto get_return_object() {
      return Task{CoroutineHandle::from_promise(*this)};
    }

    auto initial_suspend() { return std::suspend_never{}; }

    auto final_suspend() noexcept { return std::suspend_never{}; }

    void unhandled_exception() { std::terminate(); }

    void return_value(T val) { value = val; }
  };

private:
  CoroutineHandle coroutineHandle;
};

// Function that returns a Task
Task<int> asyncFunction() { co_return 42; }

int main() {
  Task<int> task = asyncFunction();
  print("Starting task...\n");

  while (!task.isDone()) {
    // Do some other work while waiting for the task to complete
    task.resume();
    print("Waiting for task to complete...\n");
  }

  std::cout << "Task result: " << task.getValue() << std::endl;

  return 0;
}

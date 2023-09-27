
#include <atomic>
#include <functional>
#include <iostream>
#include <thread>
#include <vector>

class Promise {
public:
  Promise() : resolved(false) {}
  ~Promise() {
    while (!shouldExit.load()) {
    }
  }

  void then(std::function<void()> callback) {
    if (resolved) {
      callback();
    } else {
      callbacks.push_back(callback);
    }
    shouldExit.store(false);
  }

  void resolve() const {
    resolved = true;
    for (auto callback : callbacks) {
      callback();
    }
    shouldExit.store(true);
  }

private:
  mutable bool resolved;
  mutable std::atomic<bool> shouldExit;
  std::vector<std::function<void()>> callbacks;
};

int main() {
  Promise promise;

  // Register a series of asynchronous steps
  promise.then([]() {
    std::cout << "Step 1: Performing an asynchronous task..." << std::endl;
    // Simulate an asynchronous task
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "Step 1 completed" << std::endl;
  });

  promise.then([]() {
    std::cout << "Step 2: Performing another asynchronous task..." << std::endl;
    // Simulate another asynchronous task
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "Step 2 completed" << std::endl;
  });

  promise.then([]() { std::cout << "All steps completed!" << std::endl; });

  // Simulate the completion of an asynchronous operation
  std::thread([&promise]() {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    promise.resolve();
  }).detach();

  // Continue with other tasks in the main thread
  std::cout << "Main thread continues..." << std::endl;
  std::this_thread::sleep_for(std::chrono::seconds(4));

  return 0;
}


#include <functional>
#include <iostream>
#include <vector>

class Promise {
public:
  Promise() : resolved(false) {}

  void then(std::function<void()> callback) {
    if (resolved) {
      callback();
    } else {
      callbacks.push_back(callback);
    }
  }

  void resolve() {
    resolved = true;
    for (auto callback : callbacks) {
      callback();
    }
  }

private:
  bool resolved;
  std::vector<std::function<void()>> callbacks;
};

int main() {
  Promise promise;

  promise.then([]() { std::cout << "Step 1 completed" << std::endl; });

  promise.then([]() { std::cout << "Step 2 completed" << std::endl; });

  promise.resolve(); // Simulate the completion of an asynchronous operation

  return 0;
}

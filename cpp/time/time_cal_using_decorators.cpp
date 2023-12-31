#include <chrono>
#include <functional>
#include <iostream>

// Decorator function
void exclaim(const std::function<void()> &func) {
  auto start = std::chrono::high_resolution_clock::now();
  func();
  auto end = std::chrono::high_resolution_clock::now();
  auto duration =
      std::chrono::duration_cast<std::chrono::microseconds>(end - start)
          .count();

  // Print the time interval
  std::cout << "Time interval: " << duration << " microseconds" << std::endl;
}

template <typename funcType> void exclaim(const funcType &func) {
  auto start = std::chrono::high_resolution_clock::now();
  func();
  auto end = std::chrono::high_resolution_clock::now();
  auto duration =
      std::chrono::duration_cast<std::chrono::microseconds>(end - start)
          .count();

  // Print the time interval
  std::cout << "Time interval: " << duration << " microseconds" << std::endl;
}

// Function to measure time interval
int main() {

  exclaim([]() {});

  // Measure the time interval between Function1 and Function2
  exclaim([]() {
    for (int i = 0; i < 10; ++i) {
      std::cout << "Function1" << std::endl;
    }
  });

  exclaim<std::function<void()>>([]() {
    for (int i = 0; i < 10; ++i) {
      std::cout << "Function2" << std::endl;
    }
  });

  exclaim<std::function<int()>>([]() -> int {
    for (int i = 0; i < 10; ++i) {
      std::cout << "Function3" << std::endl;
    }
    return 12;
  });
}

#include <chrono>
#include <functional>
#include <iostream>
#include <string>
#include <string_view>

// Decorator function
inline void exclaim(const std::function<void()> &func) {
  auto start = std::chrono::high_resolution_clock::now();
  func();
  auto end = std::chrono::high_resolution_clock::now();
  auto duration =
      std::chrono::duration_cast<std::chrono::microseconds>(end - start)
          .count();

  // Print the time interval
  std::cout << "Time interval: " << duration << " microseconds" << std::endl;
}

inline void exclaim(const std::function<void()> &func,
                    const std::string_view msg) {
  std::cout << msg << std::endl;
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

inline void test() {
  exclaim([]() {
    for (int i = 0; i < 10; ++i) {
      std::cout << "Function1" << std::endl;
    }
  });
}

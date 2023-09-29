#include <chrono>
#include <cstdint>
#include <exception>
#include <future>
#include <iostream>
#include <random>
#include <thread>

namespace {
constexpr int kTimes = 10;
}

int DoSomething(char c) {
  // random-number generator (use c as seed to get different sequences)
  std::default_random_engine dre(static_cast<std::int_fast32_t>(c));
  std::uniform_int_distribution<int> id(10, 1000);
  for (int i = 0; i < kTimes; ++i) {
    std::this_thread::sleep_for(std::chrono::milliseconds(id(dre)));
    std::cout.put(c).flush();
  }
  return static_cast<int>(c);
}

int main() {
  std::cout << "starting func1() in background"
            << " and func2() in foreground:" << std::endl;
  auto func1 = []() { return DoSomething('.'); };
  auto func2 = []() { return DoSomething('+'); };

  // start func1() asynchronously (now or later or never):
  auto result1 = std::async(std::move(func1));
  // call func2() synchronously (here and now)
  auto result2 = func2();

  auto result = result1.get() + result2;
  std::cout << "\nresult of func1()+func2(): " << result << std::endl;

  return 0;
}

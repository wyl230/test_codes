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
  std::cout << "starting 2 operations asynchronously" << std::endl;

  // start two loops in the background printing characters . or +
  auto f1 = std::async([] { return DoSomething('.'); });
  auto f2 = std::async([] { return DoSomething('+'); });

  // if at least one of the background tasks is running
  if (f1.wait_for(std::chrono::seconds(0)) != std::future_status::deferred ||
      f2.wait_for(std::chrono::seconds(0)) != std::future_status::deferred) {
    while (f1.wait_for(std::chrono::seconds(0)) != std::future_status::ready &&
           f2.wait_for(std::chrono::seconds(0)) != std::future_status::ready) {
      // hint to reschedule to the next thread
      std::this_thread::yield();
    }
  }

  // wait for all loops to be finished and process any exception
  try {
    f1.get();
    f2.get();
  } catch (const std::exception &e) {
    std::cout << "\nEXCEPTION: " << e.what() << std::endl;
  }
  std::cout << "\ndone" << std::endl;

  return 0;
}

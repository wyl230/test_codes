
// 4.3.2
#include "better_print.cpp"
#include <chrono>
#include <future>
#include <iostream>
#include <thread>

using namespace std::chrono_literals;
auto one_day = 24h;
auto max_time_between_messages = 30ms;

template <typename T> void do_something_with(const T &t) {
  print("we get: ", t);
}

int main(int argc, char *argv[]) {
  auto some_task = []() -> int {
    std::this_thread::sleep_for(40ms);
    std::cout << "message" << std::endl;
    return 1;
  };
  std::future<int> f = std::async(some_task);

  if (f.wait_for(std::chrono::milliseconds(35)) == std::future_status::ready) {
    do_something_with(f.get());
  }

  return 0;
}

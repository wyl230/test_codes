
// 给执行的任务一个限制的时间
#include "better_print.cpp"
#include <chrono>
#include <condition_variable>
#include <future>
#include <iostream>
#include <thread>

using namespace std::chrono_literals;
auto one_day = 24h;
auto max_time_between_messages = 30ms;

std::condition_variable cv;
bool done;
std::mutex m;
bool wait_loop() {
  auto const timeout = std::chrono::steady_clock::now() + 500ms;
  std::unique_lock<std::mutex> lk(m);
  while (!done) {
    if (cv.wait_until(lk, timeout) == std::cv_status::timeout) {
      break;
    }
  }
  return done;
}

int main(int argc, char *argv[]) {
  print("done?: ", wait_loop());
  return 0;
}

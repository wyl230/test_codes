
#include <array>
#include <iostream>
#include <queue>
#include <sltbench/BenchCore.h>

#include <future>
#include <memory>
#include <string>

using test_array = std::array<char, 655360>;
using unique_test_array = std::unique_ptr<test_array>;
//
// void f() {
//   for (int i = 0; i < 100; i++)
//     ;
// }
//
// void process_readings_async() {
//   auto h1 = async(std::launch::async, f);
//   h1.get();
// }
//
// void process_readings_plain() { f(); }
//
// void process_readings_threads() {
//   std::thread([]() { f(); }).join();
// }

// SLTBENCH_FUNCTION(process_readings_async);
// SLTBENCH_FUNCTION(process_readings_plain);
// SLTBENCH_FUNCTION(process_readings_threads);

struct Log {
  explicit Log(bool log) : log(log) {}
  bool log;
  [[nodiscard]] bool get_log() const { return log; }
};

void in_loop() {
  auto log = Log(true);
  auto cnt = 0;
  for (int i = 0; i < 3000; i++)
    for (int j = 0; j < 3000; j++) {
      if (log.get_log()) {
        cnt++;
      }
    }
}

void out_loop() {
  auto log = true;
  auto cnt = 0;
  if (log) {
    for (int i = 0; i < 3000; i++)
      for (int j = 0; j < 3000; j++) {
        cnt++;
      }
  }
}

void just() {
  auto log = true;
  auto cnt = 0;
  for (int i = 0; i < 3000; i++)
    for (int j = 0; j < 3000; j++) {
      if (static_cast<int>(log) == i) {
        cnt++;
      } else {
        cnt++;
      }
    }
}

SLTBENCH_FUNCTION(in_loop);
SLTBENCH_FUNCTION(out_loop);
SLTBENCH_FUNCTION(just);

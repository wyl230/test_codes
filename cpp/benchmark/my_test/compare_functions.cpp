
#include <array>
#include <iostream>
#include <queue>
#include <sltbench/BenchCore.h>

#include <future>
#include <memory>
#include <string>

using test_array = std::array<char, 655360>;
using unique_test_array = std::unique_ptr<test_array>;

void f() {
  for (int i = 0; i < 100; i++)
    ;
}

void process_readings_async() {
  auto h1 = async(std::launch::async, f);
  h1.get();
}

void process_readings_plain() { f(); }

void process_readings_threads() {
  std::thread([]() { f(); }).join();
}

SLTBENCH_FUNCTION(process_readings_async);
SLTBENCH_FUNCTION(process_readings_plain);
SLTBENCH_FUNCTION(process_readings_threads);

// #include "multi_task_coroutine.hpp"
#include <asio.hpp>
#include <better_print.hpp>

int main() {
  trace_us(0);
  const int n = 100;
  for (int i = 0; i < n; i++) {
    trace_us(0);
  }

  for (int i = 0; i < n; ++i) {
    trace_us(0);
  }
}

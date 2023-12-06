#include "example_multi_coro.hpp"
#include "example_return_value.hpp"
#include "simple_example.hpp"
#include "test_co_await.hpp"
#include "test_co_await_with_transform.hpp"
#include "test_co_return.hpp"
#include "test_co_return_with_return_value.hpp"
#include "test_co_yield.hpp"
// ====================================
// co_yield

int main() {
  // async_with_coroutine::example();

  // test_coroutine_main();
  // test_co_yield::test_co_yield();
  // test_co_await::test_co_await();
  // test_co_await_with_transform::test_co_await();
  // test_co_return_with_return_value::test_co_return();
  // simple_example::run_example();
  multi_coroutine::test();
}

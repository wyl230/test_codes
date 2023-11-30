#include "test_co_await.hpp"
#include "test_co_await_with_transform.hpp"
#include "test_co_return.hpp"
#include "test_co_return_with_return_value.hpp"
#include "test_co_yield.hpp"
// ====================================
// co_yield

int main() {
  // test_coroutine_main();
  // test_co_yield::test_co_yield();
  // test_co_await::test_co_await();
  test_co_await_with_transform::test_co_await();
  // test_co_return_with_return_value::test_co_return();
}

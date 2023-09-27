
#include <better_print.hpp>
#include <future>
#include <iostream>
#include <test.h>

void callback(int result) { print("we got ", result); }

void test(decltype(callback) cb) {
  std::future<int> futureResult = std::async(std::launch::async, []() {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    return 42; // 返回异步操作的结果
  });

  cb(futureResult.get());
}

void callback_future(std::future<int> &res) { print("we got ", res.get()); }

void test_cb_res_no_get(decltype(callback_future) cb) {
  std::future<int> futureResult = std::async(std::launch::async, []() {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    return 42; // 返回异步操作的结果
  });

  cb(futureResult);
}

int main(int argc, char *argv[]) {
  print(argc, argv[0]);
  print("Hello world!");
  // test(callback);
  test_cb_res_no_get(callback_future);
}

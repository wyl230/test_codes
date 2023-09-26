//
#include <functional>
#include <future>
#include <iostream>

// 回调函数，用于处理异步操作的结果
void onAsyncOperationComplete(int result) {
  std::cout << "异步操作完成，结果为: " << result << std::endl;
}

// 异步操作函数，接受一个回调函数作为参数
void performAsyncOperation(std::function<void(int)> callback) {
  // 模拟异步操作，这里使用std::async创建一个异步任务
  std::future<int> futureResult = std::async(std::launch::async, []() {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    return 42; // 返回异步操作的结果
  });

  // 等待异步操作完成并调用回调函数
  int result = futureResult.get();
  // std::cout << "异步操作完成，结果为: " << result << std::endl;
  callback(result);
}

int main() {
  // std::function<void(int)> callback = onAsyncOperationComplete;
  auto callback = onAsyncOperationComplete;
  // std::cout << sizeof(callback) << std::endl;
  // decltype(callback) test;

  // 执行异步操作，并在完成时调用回调函数
  performAsyncOperation(callback);

  // 主线程继续执行其他任务
  std::cout << "主线程继续执行..." << std::endl;

  // 等待异步操作完成
  std::this_thread::sleep_for(std::chrono::seconds(3));

  return 0;
}

// ignore this
void performAsyncOperation_using_decltype(
    decltype(onAsyncOperationComplete) callback) {
  // 模拟异步操作，这里使用std::async创建一个异步任务
  std::future<int> futureResult = std::async(std::launch::async, []() {
    std::this_thread::sleep_for(std::chrono::seconds(2));
    return 42; // 返回异步操作的结果
  });

  // 等待异步操作完成并调用回调函数
  int result = futureResult.get();
  callback(result);
}

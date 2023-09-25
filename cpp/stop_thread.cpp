
#include <atomic>
#include <iostream>
#include <thread>

std::atomic<bool> shouldExit(false);

void workerThread() {
  while (!shouldExit.load()) {
    // 执行线程的工作任务
    std::cout << "工作线程执行任务..." << std::endl;

    // 模拟工作
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }

  std::cout << "工作线程收到退出信号，正在关闭..." << std::endl;
  // 执行线程清理工作（如果有的话）
}

int main() {
  std::thread worker(workerThread);

  // 在某个特定时刻，设置 shouldExit 为 true，通知线程退出
  std::this_thread::sleep_for(std::chrono::seconds(5));
  shouldExit.store(true);

  worker.join();

  std::cout << "主线程退出" << std::endl;

  return 0;
}

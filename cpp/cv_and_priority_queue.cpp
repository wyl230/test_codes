
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>

// std::priority_queue<int> pq(); // 优先队列
std::priority_queue<int, std::vector<int>, std::greater<int>> pq;
std::mutex mtx;             // 互斥锁
std::condition_variable cv; // 条件变量

// 生产者线程函数，向优先队列中添加元素
void producer() {
  std::unique_lock<std::mutex> lock(mtx);
  for (int i = 0; i < 10; ++i) {
    // std::this_thread::sleep_for(std::chrono::milliseconds(100)); //
    // 模拟生产过程
    pq.push(i); // 添加元素到优先队列
    std::cout << "Produced: " << i << std::endl;
  }
  cv.notify_one(); // 通知一个等待的消费者线程
}

// 消费者线程函数，从优先队列中取出元素
void consumer() {
  while (true) {
    std::unique_lock<std::mutex> lock(mtx);
    // 使用条件变量等待队列不为空
    cv.wait(lock, [] { return !pq.empty(); });
    int val = pq.top(); // 从队列中取出最高优先级的元素
    pq.pop();           // 移除元素
    std::cout << "Consumed: " << val << std::endl;
  }
}

int main() {
  std::thread producerThread(producer);
  std::thread consumerThread(consumer);

  producerThread.join();
  consumerThread.join();

  return 0;
}


#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>
#include <time_cal_using_decorators.hpp>

std::mutex mtx_a, mtx_b;
std::condition_variable cv;
std::queue<int> buffer;
const int bufferSize = 5;

int n = 10000;

void producer_a() {
  for (int i = 0; i < n; ++i) {
    // std::this_thread::sleep_for(std::chrono::milliseconds(200));
    std::unique_lock<std::mutex> lock(mtx_a);
    if (buffer.size() >= bufferSize) {
      // std::cout << "Buffer is full. Producer waiting..." << std::endl;
      cv.wait(lock, [] { return buffer.size() < bufferSize; });
    }
    int data = i;
    buffer.push(data);
    // std::cout << "Produced: " << data << std::endl;
    cv.notify_all();
  }
}

void producer_b() {
  for (int i = 0; i < n; ++i) {
    // std::this_thread::sleep_for(std::chrono::milliseconds(200));
    std::unique_lock<std::mutex> lock(mtx_b);
    if (buffer.size() >= bufferSize) {
      // std::cout << "Buffer is full. Producer waiting..." << std::endl;
      cv.wait(lock, [] { return buffer.size() < bufferSize; });
    }
    int data = i;
    buffer.push(data);
    // std::cout << "Produced: " << data << std::endl;
    cv.notify_all();
  }
}

void consumer() {
  for (int i = 0; i < n; ++i) {
    // std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::unique_lock<std::mutex> lock_a(mtx_a);
    std::unique_lock<std::mutex> lock_b(mtx_b);
    if (buffer.empty()) {
      // std::cout << "Buffer is empty. Consumer waiting..." << std::endl;
      cv.wait(lock_a, [] { return !buffer.empty(); });
      cv.wait(lock_b, [] { return !buffer.empty(); });
    }
    int data = buffer.front();
    buffer.pop();
    // std::cout << "Consumed: " << data << std::endl;
    cv.notify_all();
  }
}

int test() {
  std::thread producerThread(producer_a);
  std::thread consumerThread(consumer);

  producerThread.join();
  consumerThread.join();

  return 0;
}

int main(int, char *[]) {
  exclaim([]() { test(); });
  return 0;
}

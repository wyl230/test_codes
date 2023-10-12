
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>

std::mutex mtx;
std::condition_variable cv;
std::queue<int> buffer;
const int bufferSize = 5;

void producer() {
  for (int i = 0; i < 10; ++i) {
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    std::unique_lock<std::mutex> lock(mtx);
    if (buffer.size() >= bufferSize) {
      std::cout << "Buffer is full. Producer waiting..." << std::endl;
      cv.wait(lock, [] { return buffer.size() < bufferSize; });
    }
    int data = i;
    buffer.push(data);
    std::cout << "Produced: " << data << std::endl;
    lock.unlock();
    cv.notify_all();
  }
}

void consumer() {
  for (int i = 0; i < 10; ++i) {
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::unique_lock<std::mutex> lock(mtx);
    if (buffer.empty()) {
      std::cout << "Buffer is empty. Consumer waiting..." << std::endl;
      cv.wait(lock, [] { return !buffer.empty(); });
    }
    int data = buffer.front();
    buffer.pop();
    std::cout << "Consumed: " << data << std::endl;
    lock.unlock();
    cv.notify_all();
  }
}

int main() {
  std::thread producerThread(producer);
  std::thread consumerThread(consumer);

  producerThread.join();
  consumerThread.join();

  return 0;
}

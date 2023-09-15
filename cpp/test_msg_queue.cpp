
#include "msg_queue.cpp"
#include <iostream>
#include <thread>

using std::endl;

using namespace messaging;

void producer(queue &mq) {
  for (int i = 0; i < 10; ++i) {
    std::this_thread::sleep_for(
        std::chrono::milliseconds(200)); // Simulate some work
    mq.push("Message " + std::to_string(i));
    std::cout << "Produced: Message " << i << std::endl;
  }
  std::cout << "Producer thread exiting" << std::endl;
}

void consumer(queue &mq, int id) {
  for (int i = 0; i < 5; ++i) {
    auto msg = mq.wait_and_pop();
    std::cout
        << "Consumer " << id << " received: "
        << dynamic_cast<wrapped_message<std::string> *>(msg.get())->contents
        << std::endl;
  }
  std::cout << "consumer thread exiting: " << id << std::endl;
}

int main() {
  queue mq;
  std::thread producer_thread(producer, std::ref(mq));
  std::thread consumer_thread1(consumer, std::ref(mq), 1);
  std::thread consumer_thread2(consumer, std::ref(mq), 2);

  producer_thread.join();
  consumer_thread1.join();
  consumer_thread2.join();

  return 0;
}

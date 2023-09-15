
#include "messaging.hpp" // 假设你的 messaging 头文件的名称是 messaging.hpp

#include <chrono>
#include <iostream>
#include <thread>

void receiver_thread(messaging::receiver &r) {
  for (int i = 0; i < 3; ++i) {
    // auto d = r.wait().handle<std::string>([](const std::string &msg) {
    //   std::cout << "Received message: " << msg << std::endl;
    // });

    auto d = r.wait().handle<int>([](const int &msg) {
      std::cout << "Received message: " << msg << std::endl;
    });
  }

  try {
    // Start message processing
    throw messaging::close_queue();
  } catch (const messaging::close_queue &) {
    std::cout << "Receiver thread terminated." << std::endl;
  }
}

void sender_thread(messaging::sender &s) {
  for (int i = 0; i < 3; ++i) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    // s.send(std::string("Hello from sender!"));
    s.send(123);
  }
}

int main() {
  messaging::receiver r;
  messaging::sender s = r;

  std::thread receiver_t(receiver_thread, std::ref(r));
  std::thread sender_t(sender_thread, std::ref(s));

  sender_t.join();
  receiver_t.join();

  return 0;
}

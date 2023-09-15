
#include "messaging.hpp" // 假设你的 messaging 头文件的名称是 messaging.hpp

#include <iostream>
#include <thread>

void worker_thread(messaging::receiver &r) {
  auto d = r.wait().handle<std::string>([](const std::string &msg) {
    std::cout << "Worker thread received message: " << msg << std::endl;
  });

  try {
    throw messaging::close_queue();
  } catch (const messaging::close_queue &) {
    std::cout << "Worker thread terminated." << std::endl;
  }
}

int main() {
  messaging::receiver r;
  messaging::sender s = r;

  std::thread worker_t(worker_thread, std::ref(r));

  // Main thread's dispatcher
  auto main_dispatcher =
      r.wait().handle<std::string>([&s](const std::string &msg) {
        std::cout << "Main thread received message: " << msg << std::endl;
        s.send(std::string("Hello from main dispatcher!"));
      });

  // Chain of dispatchers
  main_dispatcher.handle<std::string>([](const std::string &msg) {
    std::cout << "Main dispatcher received message: " << msg << std::endl;
  });

  s.send(std::string("Hello from main thread!"));

  worker_t.join();

  return 0;
}

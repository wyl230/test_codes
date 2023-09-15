
#include "messaging.hpp" // 假设你的 messaging 头文件的名称是 messaging.hpp

#include <iostream>
#include <thread>

using std::cout;
using std::endl;

void send_thread(messaging::sender &s) {
  for (int i = 0; i < 3; ++i) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    // s.send(std::string("Hello from sender!"));
    s.send(i);
  }
}

void worker_thread(messaging::receiver &r, int max_message_num) {
  cout << "Worker thread starting." << endl;
  for (int i = 0; i < max_message_num; ++i) {
    auto d = r.wait()
                 .handle<std::string>(
                     [](const std::string &msg) { // at first receive a string
                       std::cout << "Worker thread received message: " << msg
                                 << std::endl;
                     })
                 .handle<int>([](int value) {
                   std::cout << "Worker thread received integer: " << value
                             << std::endl;
                 })
                 .handle<double>([](double value) {
                   std::cout << "Worker thread received integer: " << value
                             << std::endl;
                 });
  }
  try {
    throw messaging::close_queue();
  } catch (const messaging::close_queue &) {
    std::cout << "Worker thread terminated." << std::endl;
  }
}

int main() {
  messaging::receiver r;
  messaging::sender s = r;

  s.send(1);
  // std::thread sending_t(send_thread, std::ref(s));
  // std::this_thread::sleep_for(std::chrono::seconds(1));
  std::thread worker_t(worker_thread, std::ref(r), 10);
  // Chain of dispatchers
  // r.wait()
  //     .handle<std::string>(
  //         [&s](const std::string &msg) { // at first receive a string
  //           std::cout << "Main thread received message: " << msg <<
  //           std::endl; s.send(42);                 // Send an integer to
  //           worker thread s.send(std::string("wer")); // Send an integer to
  //           worker thread
  //         })
  //     .handle<int>([](int value) {
  //       std::cout << "Main thread received integer: " << value << std::endl;
  //     });

  worker_t.join();
  // sending_t.join();

  return 0;
}

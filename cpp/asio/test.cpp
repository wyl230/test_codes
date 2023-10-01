#include <better_print.hpp>
#include <boost/asio.hpp>
#include <iostream>
#include <thread>
using namespace boost::asio;

int main() {

  io_context io_context;
  print(1);
  executor_work_guard<io_context::executor_type> work =
      make_work_guard(io_context);
  print(2);
  io_context::strand strand(io_context);
  print(3);

  auto st = std::thread([&io_context]() { io_context.run(); });

  // io_context.run();
  for (int i = 0;; ++i) {
    io_context.post([i]() { print(i, "qqq"); });
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }

  st.join();

  // Run the io_context in the background thread
  // std::thread io_thread([&io_context]() { io_context.run(); });

  // strand.post([]() { std::cout << "Async operation 3" << std::endl; });
  //
  // strand.post([]() { std::cout << "Async operation 4" << std::endl; });

  // Allow the run() to exit gracefully when needed
  // std::this_thread::sleep_for(std::chrono::seconds(2)); // Simulating some
  // work
  //
  // work.reset(); // Allow run() to exit.
  //
  // // Stop the io_context (run() will return as soon as possible)
  // io_context.stop();
  //
  // // Wait for the io_context thread to finish
  // io_thread.join();
  // io_context.run();
  //
  // std::cout << "IO Context has been stopped." << std::endl;

  return 0;
}

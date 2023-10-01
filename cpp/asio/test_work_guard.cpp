#include <boost/asio.hpp>
#include <iostream>

int main() {

  boost::asio::io_context io_context;
  boost::asio::executor_work_guard<boost::asio::io_context::executor_type>
      work = boost::asio::make_work_guard(io_context);
  io_context.post([]() { std::cout << "Async operation 1" << std::endl; });

  io_context.post([]() { std::cout << "Async operation 2" << std::endl; });

  // Run the io_context in the background thread
  std::thread io_thread([&io_context]() { io_context.run(); });

  // Allow the run() to exit gracefully when needed
  std::this_thread::sleep_for(std::chrono::seconds(2)); // Simulating some work

  work.reset(); // Allow run() to exit.

  // Stop the io_context (run() will return as soon as possible)
  io_context.stop();

  // Wait for the io_context thread to finish
  io_thread.join();
  io_context.run();

  std::cout << "IO Context has been stopped." << std::endl;

  return 0;
}


#include <boost/asio.hpp>
#include <iostream>
#include <thread>

void asyncOperation1(const boost::system::error_code &error) {
  std::this_thread::sleep_for(std::chrono::seconds(1));
  std::cout << "Async Operation 1 completed." << std::endl;
}

void asyncOperation2(const boost::system::error_code &error) {
  std::cout << "Async Operation 2 completed." << std::endl;
}

int main() {
  boost::asio::io_context ioContext;
  boost::asio::io_context::strand strand(ioContext);

  // 使用 strand 来排队异步操作
  strand.post([&]() {
    asyncOperation1(boost::system::error_code()); // 模拟异步操作1
  });

  strand.post([&]() {
    asyncOperation2(boost::system::error_code()); // 模拟异步操作2
  });

  // 运行 IO 上下文来处理异步操作
  ioContext.run();

  return 0;
}

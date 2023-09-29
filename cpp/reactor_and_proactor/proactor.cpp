#include <better_print.hpp>
#include <boost/asio.hpp>
#include <fstream>
#include <iostream>
#include <vector>

void handleRead(const boost::system::error_code &error, std::size_t bytesRead,
                std::vector<char> buf) {
  if (!error) {
    for (auto c : buf)
      std::cout << c;
    std::cout << "Read " << bytesRead << " bytes from the file." << std::endl;
  } else {
    std::cerr << "Error: " << error.message() << std::endl;
  }
}

int main() {
  boost::asio::io_context ioContext;
  boost::asio::io_context::strand strand(ioContext);

  // Open a file for reading
  int fileDescriptor = open("reactor.cpp", O_RDONLY);
  if (fileDescriptor < 0) {
    std::cerr << "Failed to open the file." << std::endl;
    return 1;
  }

  // Create a stream_descriptor to represent the file
  boost::asio::posix::stream_descriptor file(ioContext, fileDescriptor);

  // Create a buffer to hold read data
  const std::size_t bufferSize = 1024;
  std::vector<char> buffer(bufferSize);

  // Asynchronously read data from the file
  boost::asio::async_read(
      file, boost::asio::buffer(buffer),
      strand.wrap(
          [&](const boost::system::error_code &error, std::size_t bytesRead) {
            handleRead(error, bytesRead, buffer);
          }));

  // Run the IO context to start asynchronous operations
  ioContext.run();

  // Close the file descriptor
  close(fileDescriptor);

  return 0;
}

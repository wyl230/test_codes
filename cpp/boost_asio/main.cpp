
#include <boost/asio.hpp>
#include <iostream>

using namespace boost::asio;
using ip::tcp;

class ReactiveServer {
public:
  ReactiveServer(io_service &ioService, int port)
      : acceptor_(ioService, tcp::endpoint(tcp::v4(), port)),
        socket_(ioService) {
    startAccept();
  }

private:
  void startAccept() {
    acceptor_.async_accept(socket_, [this](
                                        const boost::system::error_code &ec) {
      if (!ec) {
        std::cout << "Accepted connection from: " << socket_.remote_endpoint()
                  << std::endl;
        handleRequest();
      }
      startAccept(); // Continue to accept new connections
    });
  }

  void handleRequest() {
    async_write(
        socket_, buffer("Hello, World!\n"),
        [](const boost::system::error_code &ec, std::size_t bytes_transferred) {
          if (!ec) {
            std::cout << "Response sent." << std::endl;
          }
        });
  }

  tcp::acceptor acceptor_;
  tcp::socket socket_;
};

int main() {
  try {
    boost::asio::io_service ioService;
    ReactiveServer server(ioService, 23011);
    ioService.run();
  } catch (std::exception &e) {
    std::cerr << "Exception: " << e.what() << std::endl;
  }

  return 0;
}

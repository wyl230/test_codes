// 为什么第二个listener执行到acceptor就停止
#include <better_print.hpp>
#include <boost/asio/co_spawn.hpp>
#include <boost/asio/detached.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/signal_set.hpp>
#include <boost/asio/use_awaitable.hpp>
#include <boost/asio/write.hpp>
#include <boost/system/error_code.hpp>
#include <boost/system/system_error.hpp>
#include <cstdio>
#include <iostream>
#include <vector>

namespace asio = boost::asio;
namespace sys = boost::system;
using boost::asio::ip::tcp;

void report_error(std::string_view component, sys::error_code ec) {
  std::cerr << component << " failure: " << ec << " ()" << ec.message()
            << ")\n";
}

asio::awaitable<void> session(tcp::socket socket) {
  try {
    char data[1024];
    for (;;) {
      std::size_t n = co_await socket.async_read_some(asio::buffer(data),
                                                      asio::use_awaitable);
      print("we receive", data);
      co_await async_write(socket, asio::buffer(data, n), asio::use_awaitable);
    }
  } catch (sys::system_error const &e) {
    if (e.code() == asio::error::eof)
      std::cerr << "Session done \n";
    else
      report_error("Session", e.code());
  }
}

// asio::awaitable<void> listener(asio::io_context &context, unsigned short
// port) {
//   // tcp::acceptor acceptor(context, {tcp::v4(), port});
//   // 端口占用时没有提示
//   try {
//     tcp::acceptor acceptor(context, {tcp::v4(), port});
//     std::cout << "Acceptor created successfully." << std::endl;
//     // 在这里可以继续使用acceptor
//     try {
//       for (;;) {
//         tcp::socket socket =
//             co_await acceptor.async_accept(asio::use_awaitable);
//         print("we get a connection ");
//         asio::co_spawn(context, session(std::move(socket)), asio::detached);
//       }
//     } catch (sys::system_error const &e) {
//       report_error("Listener", e.code());
//     }
//   } catch (const boost::system::system_error &error) {
//     if (error.code() == boost::asio::error::address_in_use) {
//       std::cerr << "Port " << port << " is already in use." << std::endl;
//     } else {
//       std::cerr << "Error: " << error.what() << std::endl;
//     }
//   }
// }

//

asio::awaitable<void> acceptConnections(tcp::acceptor &acceptor,
                                        asio::io_context &context) {
  for (;;) {
    tcp::socket socket = co_await acceptor.async_accept(asio::use_awaitable);
    print("we get a connection ");
    asio::co_spawn(context, session(std::move(socket)), asio::detached);
  }
}

void handleAcceptError(const boost::system::system_error &error,
                       unsigned short port) {
  if (error.code() == boost::asio::error::address_in_use) {
    std::cerr << "Port " << port << " is already in use." << std::endl;
  } else {
    std::cerr << "Error: " << error.what() << std::endl;
  }
}

asio::awaitable<void> listener(asio::io_context &context, unsigned short port) {
  try {
    tcp::acceptor acceptor(context, {tcp::v4(), port});
    print("Acceptor", port, "created successfully.");
    co_await acceptConnections(acceptor, context);
  } catch (const boost::system::system_error &error) {
    handleAcceptError(error, port);
  }
}

//

int main() {
  try {
    asio::io_context context;

    asio::signal_set signals(context, SIGINT, SIGTERM);
    signals.async_wait([&](auto, auto) { context.stop(); });

    std::vector<asio::awaitable<void>> listeners;

    // Start multiple listeners on different ports
    for (int port = 55555; port < 55560; port++) {
      listeners.push_back(listener(context, port));
    }

    for (auto &listen : listeners) {
      asio::co_spawn(context, std::move(listen), asio::detached);
    }

    context.run();
    std::cerr << "Server done \n";
  } catch (std::exception &e) {
    std::cerr << "Server failure: " << e.what() << "\n";
  }
}

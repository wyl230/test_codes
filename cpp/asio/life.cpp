#include "boost/asio/awaitable.hpp"
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
#include <thread>
#include <vector>

namespace asio = boost::asio;
namespace sys = boost::system;

asio::awaitable<void> f() {
  for (int cnt = 0; cnt < 10; cnt++) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    print(cnt);
  }
  return boost::asio::awaitable<void>();
}

//

int main() {
  try {
    asio::io_context context;

    asio::signal_set signals(context, SIGINT, SIGTERM);
    signals.async_wait([&](auto, auto) { context.stop(); });

    std::vector<asio::awaitable<void>> tasks;

    for (int i = 0; i < 10; i++) {
      tasks.push_back(f());
    }

    for (auto &listen : tasks) {
      asio::co_spawn(context, std::move(listen), asio::detached);
    }

    context.run();
    std::cerr << "Server done \n";
  } catch (std::exception &e) {
    std::cerr << "Server failure: " << e.what() << "\n";
  }
}

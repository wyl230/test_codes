// TCP echo server implemented with Boost.ASIO and C++20 coroutines
//
// Copyright (c) 2021 Andrzej Krzemieński (akrzemi1 at gmail dot com)
//
// Based heavily on the example by Christopher M. Kohlhoff at:
// https://www.boost.org/doc/libs/1_78_0/doc/html/boost_asio/example/cpp17/coroutines_ts/echo_server.cpp
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <asio/co_spawn.hpp>
#include <asio/detached.hpp>
#include <asio/io_context.hpp>
#include <asio/ip/tcp.hpp>
#include <asio/signal_set.hpp>
#include <asio/write.hpp>
#include <cstdio>
#include <iostream>

namespace sys = boost::system;
using asio::ip::tcp;

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
      co_await async_write(socket, asio::buffer(data, n), asio::use_awaitable);
    }
  } catch (sys::system_error const &e) {
    if (e.code() == asio::error::eof)
      std::cerr << "Session done \n";
    else
      report_error("Session", e.code());
  }
}

asio::awaitable<void> listener(asio::io_context &context, unsigned short port) {
  tcp::acceptor acceptor(context, {tcp::v4(), port});

  try {
    for (;;) {
      tcp::socket socket = co_await acceptor.async_accept(asio::use_awaitable);
      asio::co_spawn(context, session(std::move(socket)), asio::detached);
    }
  } catch (sys::system_error const &e) {
    report_error("Listener", e.code());
  }
}

int main() {
  try {
    asio::io_context context;

    asio::signal_set signals(context, SIGINT, SIGTERM);
    signals.async_wait([&](auto, auto) { context.stop(); });

    auto listen = listener(context, 55555);
    asio::co_spawn(context, std::move(listen), asio::detached);

    context.run();
    std::cerr << "Server done \n";
  } catch (std::exception &e) {
    std::cerr << "Server failure: " << e.what() << "\n";
  }
}

#include <asio.hpp>
#include <asio/io_context.hpp>
#include <iostream>
#include <string>

using asio::awaitable;
using asio::co_spawn;
using asio::detached;
using asio::io_context;
using asio::use_awaitable;
using asio::ip::tcp;
using namespace std;

awaitable<void> session(tcp::socket socket) {
  string data;
  cout << "Client connected: " << socket.remote_endpoint() << '\n';
  while (data != "quit") {
    data.clear();
    co_await asio::async_read_until(socket, asio::dynamic_buffer(data), '\n',
                                    use_awaitable); // line-by-line reading
    if (data != "")
      co_await asio::async_write(socket, asio::buffer(data), use_awaitable);
  }
  cout << "Client disconnected: " << socket.remote_endpoint() << '\n';
}

awaitable<void> listener(io_context &ctx, unsigned short port) {
  tcp::acceptor acceptor(ctx, {tcp::v4(), port});
  cout << "Server listening on port " << port << "..." << endl;
  while (true) {
    tcp::socket socket = co_await acceptor.async_accept(use_awaitable);
    co_spawn(ctx, session(move(socket)), detached);
  }
}

int main(int argc, char *argv[]) {

  io_context io_context;

  asio::signal_set signals(io_context, SIGINT, SIGTERM);
  signals.async_wait([&](auto, auto) { io_context.stop(); });

  co_spawn(io_context, listener(io_context, 55555), asio::detached);
  co_spawn(io_context, listener(io_context, 55556), asio::detached);
  io_context.run();
}

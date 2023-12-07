#include "io_context.h"
// make sure io_context.h is above awaiters.h
#include "awaiters.h"
#include "print.hpp"

task<bool> inside_loop(Socket &socket) {
  PRINT;
  char buffer[1024] = {0};
  ssize_t recv_len = co_await socket.recv(buffer, sizeof(buffer));
  ssize_t send_len = 0;
  printf("recv_len=%ld\n", recv_len);
  while (send_len < recv_len) {
    ssize_t res = co_await socket.send(buffer + send_len, recv_len - send_len);
    if (res <= 0) {
      co_return false;
    }
    send_len += res;
  }

  std::cout << "Done send " << send_len << "\n";
  if (recv_len <= 0) {
    co_return false;
  }
  printf("%s\n", buffer);
  co_return true;
}

task<> echo_socket(std::shared_ptr<Socket> socket) {
  PRINT;
  for (;;) {
    print("========begin========");

    bool b = co_await inside_loop(*socket);
    if (!b)
      break;
    print("=========end=========");
  }
}

task<> accept(Socket &listen) {
  PRINT;
  for (;;) {
    PRINTx("in loop");
    auto socket = co_await listen.accept();
    auto t = echo_socket(socket);
    t.resume();
  }
}

int main(int argc, char *argv[]) {
  PRINT;
  IoContext io_context;
  PRINT;
  Socket listen{argv[1], io_context};
  PRINT;
  auto t = accept(listen);
  PRINT;
  t.resume();
  PRINT;

  io_context.run(); // 启动事件循环
  PRINT;
}

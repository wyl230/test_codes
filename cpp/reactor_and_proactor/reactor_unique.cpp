
#include <better_print.hpp>
#include <fcntl.h>
#include <iostream>
#include <map>
#include <memory>
#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>
#include <time_cal_using_decorators.hpp>
#include <unistd.h>
#include <vector>

class EventHandler {
public:
  virtual void handleEvent(int fd) = 0;
  virtual void handleEvent() = 0;
  virtual int getFd() const = 0;
};

class TestHandler : public EventHandler {
public:
  TestHandler() {}
  ~TestHandler() {}

  void handleEvent() override {
    for (int i = 0; i < 100; ++i) {
    }
  }

  void handleEvent(int) override {}
  int getFd() const override { return 0; }
};

class FileHandler : public EventHandler {
public:
  FileHandler(const std::string &filename) : filename(filename) {
    fd = ::open(filename.c_str(), O_RDONLY);
    if (fd == -1) {
      throw std::runtime_error("Failed to open file");
    }
  }

  ~FileHandler() {
    if (fd != -1) {
      ::close(fd);
    }
  }

  void handleEvent() override {}

  void handleEvent(int fd) override {
    char buffer[1024];
    ssize_t bytesRead = ::read(fd, buffer, sizeof(buffer));
    if (bytesRead > 0) {
      buffer[bytesRead] = '\0';
      std::cout << "Read from file: " << filename << " : " << buffer
                << std::endl;
    } else {
      std::cout << "Error reading from file: " << filename << std::endl;
    }
  }

  int getFd() const override { return fd; }

private:
  int fd;
  std::string filename;
};

class Reactor {
public:
  void registerHandler(std::unique_ptr<EventHandler> handler) {
    int fd = handler->getFd();
    handlers[fd] = std::move(handler);
  }

  void removeHandler(int fd) {
    printf("Removing handler for fd %d\n", fd);
    handlers.erase(fd);
    printf("Removed handler for fd %d\n", fd);
  }

  void runEventLoop() {
    while (true) {
      printf("Running event loop\n");
      fd_set readfds;
      FD_ZERO(&readfds);
      int maxfd = -1;
      printf("Adding handlers\n");

      for (const auto &pair : handlers) {
        int fd = pair.first;
        FD_SET(fd, &readfds);
        maxfd = std::max(maxfd, fd);
      }
      printf("Added handlers\n");

      int ready = select(maxfd + 1, &readfds, nullptr, nullptr, nullptr);

      if (ready == -1) {
        perror("select");
        break;
      }

      std::vector<int> elementsToRemove;

      for (const auto &pair : handlers) {
        int fd = pair.first;
        if (FD_ISSET(fd, &readfds)) {
          pair.second->handleEvent(fd);
          elementsToRemove.push_back(fd); // 记录要删除的元素
        }
      }

      // 遍历临时容器并删除元素
      for (int fdToRemove : elementsToRemove) {
        removeHandler(fdToRemove);
      }
      if (handlers.empty()) {
        break;
      } else {
        print("size", handlers.size());
      }
    }
  }

private:
  std::map<int, std::unique_ptr<EventHandler>> handlers;
};

void test() {
  exclaim([] {
    Reactor reactor;
    for (int i = 0; i < 10000000; ++i) {
      std::unique_ptr<TestHandler> testHandler =
          std::make_unique<TestHandler>();
      reactor.registerHandler(std::move(testHandler));
    }
  });
  // reactor.runEventLoop();
}

int main() {
  test();
  // Reactor reactor;
  // std::unique_ptr<FileHandler> fileHandler =
  //     std::make_unique<FileHandler>("example.txt");
  // reactor.registerHandler(std::move(fileHandler));
  // reactor.runEventLoop();
  return 0;
}

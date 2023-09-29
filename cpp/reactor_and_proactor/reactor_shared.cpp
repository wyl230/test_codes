
#include <better_print.hpp>
#include <fcntl.h>
#include <iostream>
#include <map>
#include <memory>
#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>
#include <unistd.h>
#include <vector>

class EventHandler : public std::enable_shared_from_this<EventHandler> {
public:
  virtual void handleEvent(int fd) = 0;
};

class Reactor {
public:
  void registerHandler(int fd, std::shared_ptr<EventHandler> handler) {
    handlers[fd] = handler;
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
      printf("Added handlers\n");

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
    }
  }

private:
  std::map<int, std::shared_ptr<EventHandler>> handlers;
};

class FileHandler : public EventHandler,
                    public std::enable_shared_from_this<FileHandler> {
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

  int getFd() const { return fd; }

  std::shared_ptr<FileHandler> shared_from_this() {
    return std::static_pointer_cast<FileHandler>(
        EventHandler::shared_from_this());
  }

private:
  int fd;
  std::string filename;
};

int main() {
  Reactor reactor;
  std::shared_ptr<FileHandler> fileHandler =
      std::make_shared<FileHandler>("example.txt");
  reactor.registerHandler(fileHandler->getFd(), fileHandler);
  reactor.runEventLoop();
  return 0;
}

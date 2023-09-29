#include <better_print.hpp>
#include <fcntl.h>
#include <map>
#include <memory>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

class EventHandler {
public:
  virtual void handleEvent(int fd) = 0;
};

using EventHandlerPtr = std::unique_ptr<EventHandler>;
class Reactor {

public:
  void registerHandler(int fd, EventHandlerPtr handler) {
    print("registerHandler", fd);
    handlers[fd] = std::move(handler);
  }

  void removeHandler(int fd) { handlers.erase(fd); }

  void runEventLoop() {
    while (true) {
      fd_set readfds;
      FD_ZERO(&readfds);
      int maxfd = -1;

      for (const auto &pair : handlers) {
        int fd = pair.first;
        FD_SET(fd, &readfds);
        maxfd = std::max(maxfd, fd);
      }

      int ready = select(maxfd + 1, &readfds, nullptr, nullptr, nullptr);

      if (ready == -1) {
        perror("select");
        break;
      }

      for (const auto &pair : handlers) {
        int fd = pair.first;
        if (FD_ISSET(fd, &readfds)) {
          pair.second->handleEvent(fd);
          removeHandler(fd);
        }
      }
    }
  }

private:
  std::map<int, EventHandlerPtr> handlers;
};

class FileHandler : public EventHandler {
public:
  FileHandler(const std::string &filename) : filename(filename) {
    fd = open(filename.c_str(),
              O_RDONLY); // Use ::open to access global scope O_RDONLY
    print("FileHandler", fd);
  }

  ~FileHandler() {
    if (fd != -1) {
      print("close", fd);
      close(fd); // Use ::close to access global scope close
    }
  }

  void handleEvent(int fd) override {
    print("handleEvent", fd);
    char buffer[1024];
    ssize_t bytesRead = read(
        fd, buffer, sizeof(buffer)); // Use ::read to access global scope read
    if (bytesRead > 0) {
      buffer[bytesRead] = '\0';
      std::cout << "Read from file: " << filename << " : " << buffer
                << std::endl;
    } else {
      std::cout << "Error reading from file: " << filename << std::endl;
    }
  }

  int getFd() const { // Add a getFd function
    print("getFd", fd);
    return fd;
  }

private:
  int fd;
  std::string filename;
};

using FileHandlerPtr = std::unique_ptr<FileHandler>;

int main() {

  Reactor reactor;
  // FileHandler fileHandler("example.txt");
  FileHandlerPtr fileHandlerPtr = std::make_unique<FileHandler>("example.txt");
  // FileHandler fileHandler2("reactor.cpp");

  if (fileHandlerPtr->getFd() != -1) {
    print("FileHandler created");
    reactor.registerHandler(fileHandlerPtr->getFd(), std::move(fileHandlerPtr));
    reactor.runEventLoop();
  } else {
    print("FileHandler not created");
  }

  return 0;
}

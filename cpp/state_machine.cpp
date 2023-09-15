// 4.15
#include <functional>
#include <iostream>
#include <string>
#include <thread>
using std::cout;
using std::endl;

namespace messaging {

class receiver {
public:
  std::string msg;
  receiver wait() {
    cout << "waiting" << endl;
    return *this;
  }

  template <typename T>
  void handle(std::function<void(std::string const &)> handler) {
    cout << "handling" << endl;
    handler("234");
  }
};

class sender {
public:
  void send(std::string const &msg) { std::cout << msg << std::endl; }
};

class close_queue {
public:
  virtual ~close_queue() {}
};

} // namespace messaging

struct card_inserted {
  std::string account;
};

class atm {
  // std::string state;
  messaging::receiver incoming;
  messaging::sender bank;
  messaging::sender interface_hardware;
  void (atm::*state)();
  std::string account;
  std::string pin;
  void waiting_for_card() {
    cout << "Waiting for card" << endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // 发送给界面一个消息，内容为 waiting for card
    interface_hardware.send(display_enter_card());
    incoming.wait().handle<card_inserted>([&](std::string const &msg) {
      cout << "Card inserted" << endl;
      account = msg;
      // account = msg.account;
      pin = "";
      interface_hardware.send(display_enter_pin());
      state = &atm::getting_pin;
    });
  }
  void getting_pin() {
    cout << "Getting pin" << endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    interface_hardware.send(display_enter_pin());
  }
  std::string display_enter_card() { return "please Enter your card!"; }

  std::string display_enter_pin() { return "Enter card pin"; }

public:
  void run() {
    state = &atm::waiting_for_card;
    try {
      for (;;) {
        (this->*state)();
      }
    } catch (messaging::close_queue const &) {
    }
  }
};

int main(int argc, char *argv[]) {
  atm atm;
  atm.run();
  return 0;
}

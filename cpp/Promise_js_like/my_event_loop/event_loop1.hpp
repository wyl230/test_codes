#pragma once
#include "../to_be_checked.hpp"
#include <chrono>
#include <functional>
class MessageLoop;
// to be checked
class Error {
public:
  Error(int code, std::string message)
      : code_(code), message_(std::move(message)) {}

  int GetCode() const { return code_; }
  const std::string &GetMessage() const { return message_; }

private:
  int code_;
  std::string message_;
};
// check above

// 定义时钟类型
using SystemClock = std::chrono::system_clock;
using MonotonicClock = std::chrono::steady_clock;

// 定义时间点类型
using Ts = SystemClock::time_point;
using Tm = MonotonicClock::time_point;

enum class Severity { kUrgent, kCritical, kNormal };

class DispatcherProvider {
public:
};

class ExecutorProvider {
public:
};

class TimerProvider {
public:
};

// class TimerWheelProvider {
// public:
//                                    Ts) = 0;
// };

// class PollerProvider {
// public:
//   // asynchronous operation returns active events
//                             std::optional<MilliSeconds> timeout) = 0;
// };

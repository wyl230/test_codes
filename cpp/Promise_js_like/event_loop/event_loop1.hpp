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
  virtual void Dispatch(MessageLoop *, std::function<void()> &&handler) = 0;
  virtual ~DispatcherProvider() {}
};

class ExecutorProvider {
public:
  virtual void Post(std::function<void()> &&handler, Severity) = 0;
  virtual ~ExecutorProvider() {}
};

class TimerProvider {
public:
  virtual void RunAt(std::function<void(Error &&)> &&handler, Tm) = 0;
  virtual ~TimerProvider() {}
};

// class TimerWheelProvider {
// public:
//   virtual TimerToken AddTimerEvent(std::function<void(Error &&)> &&handler,
//                                    Ts) = 0;
//   virtual ~TimerWheelProvider() {}
// };

// class PollerProvider {
// public:
//   // asynchronous operation returns active events
//   virtual Promise<int> Poll(int fd, int event,
//                             std::optional<MilliSeconds> timeout) = 0;
//   virtual ~PollerProvider() {}
// };

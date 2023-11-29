#pragma once
#include "../to_be_checked.hpp"
#include <functional>
class MessageLoop;

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

class TimerWheelProvider {
public:
  virtual TimerToken AddTimerEvent(std::function<void(Error &&)> &&handler,
                                   Ts) = 0;
  virtual ~TimerWheelProvider() {}
};

class PollerProvider {
public:
  // asynchronous operation returns active events
  virtual Promise<int> Poll(int fd, int event,
                            std::optional<MilliSeconds> timeout) = 0;
  virtual ~PollerProvider() {}
};

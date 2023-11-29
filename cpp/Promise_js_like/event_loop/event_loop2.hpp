#pragma once
#include "../to_be_checked.hpp"
#include "event_loop/event_loop1.hpp"
#include "intrusive_list_base.hpp"
#include <boost/asio.hpp>
#include <chrono>
#include <functional>
#include <memory>
#include <queue>

class MessageLoop;

class MessageLoop : public TimerProvider,
                    public DispatcherProvider,
                    public ExecutorProvider,
                    // public TimerWheelProvider,
                    // public PollerProvider,
                    public std::enable_shared_from_this<MessageLoop> {
public:
  enum Type {
    kTypeDefault,
    kTypeIO,
  };

  Type type() const { return type_; }

  explicit MessageLoop(Type type);

  ~MessageLoop() override;

  static MessageLoop *Current();

public:
  struct DestructionObserverTag {};
  class DestructionObserver : public IntrusiveListBase<DestructionObserverTag> {
  public:
    virtual void WillDestruct() = 0;
    virtual ~DestructionObserver() {}
  };

  void AddDestructionObserver(DestructionObserver *ob) {
    dctor_observers_.push_back(*ob);
  }
  void RemoveDestructionObserver(DestructionObserver *ob) { ob->unlink(); }

public:
  struct TaskObserverTag {};
  class TaskObserver : public IntrusiveListBase<TaskObserverTag> {
  public:
    virtual void HandleTaskBefore() = 0;
    virtual void HandleTaskAfter() = 0;
    virtual ~TaskObserver() {}
  };

  void AddTaskObserver(TaskObserver *ob) { task_observers_.push_back(*ob); }
  void RemoveTaskObserver(TaskObserver *ob) { ob->unlink(); }

public:
  using Proactor = boost::asio::io_context;
  virtual Proactor *proactor() { return nullptr; }
  virtual const Proactor *proactor() const { return nullptr; }

public:
  enum State {
    kInit,
    kRunning,
    kShowdown,
    kGracefulShotdown,
  };

  State state() const { return state_; }
  void set_state(State state) { state_ = state; }
  bool IsRunning() const { return state() == kRunning; }

  virtual void Run() = 0;
  virtual void Shutdown() = 0;
  virtual void GracefulShutdown() = 0;

public:
  bool IsInMessageLoopThread() const { return Current() == this; }

  void Dispatch(MessageLoop *loop, std::function<void()> &&handler) override {
    if (loop->IsInMessageLoopThread()) {
      handler();
    } else {
      loop->remote_executor()->Post(std::move(handler));
    }
  }

public:
  class LocalExecutor : public Executor {
  public:
    LocalExecutor() = default;

    LocalExecutor(LocalExecutor &&) = default;
    LocalExecutor &operator=(LocalExecutor &&) = default;

    void Post(std::function<void()> &&handler) override {
      handlers_.push(std::move(handler));
    }

    bool empty() const { return handlers_.empty(); }
    std::size_t size() const { return handlers_.size(); }
    std::function<void()> Pop() {
      auto result = std::move(handlers_.front());
      handlers_.pop();
      return result;
    }

  private:

    std::queue<std::function<void()>> handlers_;
    std::queue<std::function<void()>> g_task_queue;

  };
  void Post(std::function<void()> &&handler,
            Severity severity = Severity::kNormal) override {
    switch (severity) {
    case Severity::kUrgent:
      urgent_.Post(std::move(handler));
      break;
    case Severity::kCritical:
      critical_.Post(std::move(handler));
      break;
    case Severity::kNormal:
      normal_.Post(std::move(handler));
      break;
    }
  }
  void PostTask(std::function<void()> &&handler, Severity severity) {
    Post(std::move(handler), severity);
  }

public:
#define Duration std::chrono::duration
#define DurationCast std::chrono::duration_cast
  Ts WallNow() { return SystemClock::now(); }
  Tm MonoNow() { return MonotonicClock::now(); }
  std::int64_t NowUnix() {
    return DurationCast<std::chrono::milliseconds>(WallNow().time_since_epoch())
        .count();
  }

  void RunAt(std::function<void(Error &&)> &&handler, Tm tm) override {}

  template <class Rep, class Period>
  void RunAfter(std::function<void(Error &&)> &&handler,
                Duration<Rep, Period> delay) {
    RunAt(std::move(handler), MonoNow() + delay);
  }

  // public:
  //   TimerToken AddTimerEvent(std::function<void(Error &&)> &&handler,
  //                            Ts ts) override {
  //     return {};
  //   }
  //
  // public:
  //   Promise<int> Poll(int fd, int event,
  //                     std::optional<MilliSeconds> timeout) override {
  //     return {};
  //   }

public:
  Executor *executor() { return &normal_; }
  virtual Executor *remote_executor() = 0;

protected:
  void RunOneTask(std::function<void()> &&handler) {
    std::for_each(task_observers_.begin(), task_observers_.end(),
                  [](TaskObserver &ob) mutable { ob.HandleTaskBefore(); });
    handler();
    std::for_each(task_observers_.begin(), task_observers_.end(),
                  [](TaskObserver &ob) mutable { ob.HandleTaskAfter(); });
  }

  void RunTasks() {
    LocalExecutor *executors[3]{&urgent_, &critical_, &normal_};

    std::vector<std::function<void()>> tasks;
    tasks.reserve(urgent_.size() + critical_.size() + normal_.size());
    for (auto *executor : executors) {
      while (!executor->empty()) {
        tasks.emplace_back(executor->Pop());
      }
    }

    for (auto &task : tasks) {
      RunOneTask(std::move(task));
    }
  }

protected:
  Type type_;
  State state_;

  LocalExecutor urgent_;
  LocalExecutor critical_;
  LocalExecutor normal_;

  IntrusiveList<TaskObserver, TaskObserverTag> task_observers_;
  IntrusiveList<DestructionObserver, DestructionObserverTag> dctor_observers_;
};
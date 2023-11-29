#pragma once
#include "promise_status_machine.hpp"
#include <cstdint>
#include <memory>
// PromiseStateBase 是状态基类，只有一个状态机成员 status_。Promise
// 可以组织成链，前一个 Promise
// 可以传递数据到后一个，因此，存在双向指针相关的方法 previous 和
// next，以及用来在链上传递数据的 Propagator 方法。
//
// 由于 Resolver 使用了观察者模式，且需要维护 Promise
// 链上的生命周期，PromiseStateBase 继承了 enable_shared_from_this，并以
// shared_ptr 形态存在。这样，只要后一个 Promise 持有前一个的 shared_ptr
// ，最终，我们只需要维护最后一个 Promise 的状态，就可以保证整个 Promise
// 链上的生命周期。反之，我们释放最后一个 Promise，那么链上的所有 Promise
// 都会自动释放。

class Executor; // TODO:

class PromiseStateBase : public std::enable_shared_from_this<PromiseStateBase> {
public:
  PromiseStateBase() = default;
  virtual ~PromiseStateBase() {}

  struct Propagator {
    virtual void PropagateResult(void *) = 0;
    virtual void PropagatePromise(void *) = 0;

    virtual ~Propagator() {}
  };

public:
  virtual Propagator *propagator() const { return nullptr; }
  virtual Propagator *next_propagator() const { return nullptr; }

  virtual PromiseStateBase *previous() const { return nullptr; }
  virtual PromiseStateBase *next() const { return nullptr; }

  // when the node goes out of the scope, detach the promise chain
  virtual void DetachFromChain() = 0;

public:
  void Cancel() {
    for (auto c = this; c; c = c->next()) {
      if (c->ToCancelled()) {
        c->OnCancel();
      }
    }
  }
  virtual void OnCancel() {}

public:
  virtual bool HasHandler() const = 0;
  virtual Executor *GetExecutor() const = 0;

public:
  PromiseStatus status() const { return status_.status(); }

  bool IsDone() const { return status_.IsDone(); }
  bool IsPending() const { return status_.IsPending(); }
  bool IsSatisfied() const { return status_.IsSatisfied(); }
  bool IsUnsatisfied() const { return status_.IsUnsatisfied(); }
  bool IsSettled() const { return status_.IsSettled(); }

  bool IsEmpty() const { return status_.IsEmpty(); }
  bool IsPreFulfilled() const { return status_.IsPreFulfilled(); }
  bool IsFulfilled() const { return status_.IsFulfilled(); }
  bool IsPreRejected() const { return status_.IsPreRejected(); }
  bool IsRejected() const { return status_.IsRejected(); }
  bool IsCancelled() const { return status_.IsCancelled(); }

public:
  bool ToPreFulfilled() { return status_.ToPreFulfilled(); }
  bool ToFulfilled() { return status_.ToFulfilled(); }
  bool ToPreRejected() { return status_.ToPreRejected(); }
  bool ToRejected() { return status_.ToRejected(); }
  bool ToCancelled() { return status_.ToCancelled(); }
  void Force(PromiseStatus s) { status_.Force(s); }

private:
  PromiseStatusMachine status_;
};

#include "promise_state_base.hpp"
#include "promise_status_machine.hpp"
#include "to_be_checked.hpp"
#include <cstdint>
#include <functional>
#include <memory>
// PromiseState 模版类较为复杂，它持有了 Promise
// 必需的状态，包括双向指针成员、回调函数成员、执行器 Executor*
// 成员，以及异步任务返回值成员。PromiseState 有几个核心的方法：
//
// Resolve 表示 Promise 得到了一个值
// Reject 表示 Promise 得到了一个错误
// Cancel 表示取消 Promise ，它会清理内部状态，并保证回调函数不会被调用
// Attach 表示将某个 Promise 加入到链上，提供多种重载版本，对应不同的返回值类型

template <typename T>
class PromiseState : public PromiseStateBase,
                     public PromiseStateBase::Propagator {
public:
  using ValueType = T;
  using Callback = std::function<void(Result<T> &&)>;
  using Propagator = PromiseStateBase::Propagator;

  PromiseState()
      : PromiseStateBase(), PromiseStateBase::Propagator(), storage_(),
        callback_(), executor_(nullptr), previous_(), next_(nullptr) {}

  PromiseState(PromiseState &&) = default;
  PromiseState &operator=(PromiseState &&) = default;

  ~PromiseState() override {
    if (previous_) {
      previous_->DetachFromChain();
    }
  }

public:
  template <typename U> bool Resolve(U &&value) {
    if (IsEmpty()) {
      storage_.emplace(std::forward<U>(value));
      ToPreFulfilled();
      TryInvokeCallback();
      return true;
    }
    return false;
  }

  bool Reject(base::Error &&e) {
    if (IsEmpty()) {
      storage_.emplace(std::move(e));
      ToPreRejected();
      TryInvokeCallback();
      return true;
    }
    return false;
  }

  void Cancel() {
    if (IsEmpty() || IsPending()) {
      callback_ = {};
      storage_ = std::nullopt;
      ToCancelled();
    }
  }

  template <typename U> void Watch(PromiseState<U> *other) {
    previous_ = other->shared_from_this();
    other->set_next(this);
  }

public:
  Propagator *propagator() const override {
    return const_cast<Propagator *>(static_cast<const Propagator *>(this));
  }

  Propagator *next_propagator() const override {
    return next_ ? next_->propagator() : nullptr;
  }

  void set_next(PromiseStateBase *p) { next_ = p; }
  PromiseStateBase *next() const override { return next_; }
  PromiseStateBase *previous() const override { return previous_.get(); }

  void DetachFromChain() override { set_next(nullptr); }

public:
  void PropagatePromise(void *) override;
  void PropagateResult(void *result) override {
    auto *r = reinterpret_cast<Result<T> *>(result);
    if (*r) {
      Resolve(r->PassResult());
    } else {
      Reject(r->PassError());
    }
  }

public:
  Executor *GetExecutor() const override { return executor_; }
  bool HasHandler() const override { return static_cast<bool>(callback_); }

public:
  template <typename F, typename RT = std::invoke_result_t<F, T>,
            std::enable_if_t<std::is_void<RT>::value, int> = 0>
  void Attach(F &&callback, Executor *executor);

  template <typename U, typename F, typename RT = std::invoke_result_t<F, T>,
            std::enable_if_t<IsResult<RT>::value, int> = 0>
  void Attach(PromiseState<U> *next, F &&callback, Executor *exectuor);

  template <typename U, typename F, typename RT = std::invoke_result_t<F, T>,
            std::enable_if_t<IsPromise<RT>::value, int> _ = 0>
  void Attach(PromiseState<U> *next, F &&callback, Executor *executor);

  template <typename F, typename RT = std::invoke_result_t<F, T>,
            std::enable_if_t<IsResult<RT>::value, int> = 0>
  void Attach(F &&callback, Executor *exectuor);

private:
  void TryInvokeCallback() {
    if (callback_ && IsPending()) {
      auto cb = [this]() -> void {
        switch (status()) {
        case PromiseStatus::kPreFulfilled:
          CHECK(ToFulfilled());
          InvokeCallback();
          break;

        case PromiseStatus::kPreRejected:
          CHECK(ToRejected());
          InvokeCallback();
          break;

        default:
          break;
        }
      };

      RunInExecutor(BindWeak(this, std::move(cb)));
    }
  }

  void InvokeCallback() {
    DCHECK(storage_);
    auto tmp = base::Pass(&callback_);
    NO_EXCEPT(tmp(std::move(storage_.value())));
  }

  template <typename F> void RunInExecutor(F &&callback) {
    if (executor_) {
      executor_->Post(std::move(callback));
    } else {
      NO_EXCEPT(callback());
    }
  }

  void AddCallback(Callback &&cb, Executor *executor) {
    callback_ = std::move(cb);
    executor_ = executor;
    TryInvokeCallback();
  }

private:
  std::optional<Result<T>> storage_;

  Callback callback_;
  Executor *executor_;

  // hold a strong pointer to previous promise
  // so when we hold the last promise, the whole promises are alive
  std::shared_ptr<PromiseStateBase> previous_;

  // the next promise pointer is mainly used to propagate result/promise
  PromiseStateBase *next_;

  template <typename U> friend class Promise;

  DISALLOW_COPY_AND_ASSIGN(PromiseState);
};

#pragma once
#include "promise_resolver.hpp"
#include "promise_state.hpp"
#include "promise_status_machine.hpp"
#include "to_be_checked.hpp"
#include <cstdint>
#include <functional>
#include <memory>
#include <optional>
#include <print.hpp>

/* Promise 的实现。它内部只有一个成员，即
 * shared_ptr<PromiseState>。其内部绝大部分功能，都是委托 PromiseState
 * 来实现。但也出现了几个新面孔， */
/* ThenAll 表示一个容器中的所有 Promise 都处于就绪态，触发异步回调 */
/* ThenAny 表示一个容器中存在一个 Promise 处于就绪态，触发异步回调 */

template <typename T> class Promise {
public:
  using ValueType = T;
  using ResolverType = PromiseResolver<T>;

  Promise() : state_(std::make_shared<_::PromiseState<T>>()) {}

  explicit Promise(std::shared_ptr<_::PromiseState<T>> &&p)
      : state_(std::move(p)) {}

  Promise(Promise &&) = default;
  Promise &operator=(Promise &&) = default;

public:
  template <typename U> bool Resolve(U &&value) {
    return state_->Resolve(std::forward<U>(value));
  }

  bool Reject(base::Error &&e) { return state_->Reject(std::move(e)); }

  void Cancel() { state_->Cancel(); }

  ResolverType GetResolver() { return ResolverType{state_}; }

public:
  bool IsDone() const { return state_->IsDone(); }
  bool IsPending() const { return state_->IsPending(); }
  bool IsSatisfied() const { return state_->IsSatisfied(); }
  bool IsUnsatisfied() const { return state_->IsUnsatisfied(); }
  bool IsSettled() const { return state_->IsSettled(); }

  bool IsEmpty() const { return state_->IsEmpty(); }
  bool IsPreFulfilled() const { return state_->IsPreFulfilled(); }
  bool IsFulfilled() const { return state_->IsFulfilled(); }
  bool IsPreRejected() const { return state_->IsPreRejected(); }
  bool IsRejected() const { return state_->IsRejected(); }
  bool IsCancelled() const { return state_->IsCancelled(); }

public:
  bool HasHandler() const { return state_->HasHandler(); }
  Executor *GetExecutor() const { return state_->GetExecutor(); }

public:
  template <typename F, typename RT = std::invoke_result_t<F, T>,
            typename R = typename RT::ValueType,
            std::enable_if_t<IsPromise<RT>::value, int> _ = 0>
  Promise<R> Then(F &&, Executor *);

  template <typename F, typename RT = std::invoke_result_t<F, T>,
            typename R = typename RT::ValueType,
            std::enable_if_t<IsResult<RT>::value, int> _ = 0>
  Promise<R> Then(F &&, Executor *);

  template <typename F, typename RT = std::invoke_result_t<F, T>,
            std::enable_if_t<std::is_void_v<RT>, int> _ = 0>
  void Then(F &&, Executor *);

private:
  template <typename U> struct DeduceAllPromise;

  template <template <typename...> class Cntr, typename Tp>
  struct DeduceAllPromise<Result<Cntr<Promise<Tp>>>> {
    using VauleType = Cntr<Tp>;
  };

  template <typename U> struct DeduceAnyPromise;

  template <template <typename...> class Cntr, typename Tp>
  struct DeduceAnyPromise<Result<Cntr<Promise<Tp>>>> {
    using ValueType = Tp;
  };

  template <typename U> using DeduceRacePromise = DeduceAnyPromise<U>;

public:
  // the functor |F| of following methods should return a promise container
  template <typename F, typename RT = std::invoke_result_t<F, Result<T>>,
            typename DeduceType = typename DeduceAllPromise<RT>::VauleType,
            typename R = DeduceType>
  Promise<R> ThenAll(F &&f, Executor *executor);

  template <typename F, typename RT = std::invoke_result_t<F, Result<T>>,
            typename DeduceType = typename DeduceAnyPromise<RT>::ValueType,
            typename R = DeduceType>
  Promise<R> ThenAny(F &&f, Executor *executor);

  template <typename F, typename RT = std::invoke_result_t<F, Result<T>>,
            typename DeduceType = typename DeduceRacePromise<RT>::ValueType,
            typename R = DeduceType>
  Promise<R> ThenRace(F &&f, Executor *executor);

protected:
  std::shared_ptr<_::PromiseState<T>> state() { return state_; }
  _::PromiseState<T> *state_ptr() { return state_.get(); }

  template <typename U, typename F>
  void DoThen(_::PromiseState<U> *promise, F &&functor, Executor *executor);

  template <typename F> void DoThen(F &&functor, Executor *executor);

private:
  std::shared_ptr<_::PromiseState<T>> state_;

  template <typename U> friend class Promise;

  template <typename U> friend class _::PromiseState;

  DISALLOW_COPY_AND_ASSIGN(Promise);
};

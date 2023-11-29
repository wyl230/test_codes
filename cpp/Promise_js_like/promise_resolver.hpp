#pragma once
#include "promise_state.hpp"
#include "promise_status_machine.hpp"
#include "to_be_checked.hpp"
#include <cstdint>
#include <functional>
#include <memory>
#include <optional>
#include <print.hpp>
/* PromiseResolver 是个观察者，因此，它内部有个 weak_ptr。观察者也可以调用
 * Resolve、 Reject 和 Cancel 方法。实际上，它们先会尝试提升 weak_ptr 为
 * shared_ptr，如果成功，则表示 Promise
 * 仍在，可以安全调用，否则是个空操作。同时，PromiseState 保证已经被 Resolve、
 * Reject 或 Cancel，重复调用也是空操作 */

template <typename T> class PromiseResolver {
public:
  template <typename U> bool Resolve(U &&);

  bool Reject(base::Error &&);
  void Cancel();

  void Reset() { ptr_.reset(); }

public:
  // check whether the promise's callback has been invoked
  std::optional<bool> IsDone() const;

  // check whether the promise has been initialized
  std::optional<bool> IsEmpty() const;

  // check whether the result has been settled, maybe not invoke callback
  std::optional<bool> IsSettled() const;

  // check the promise has invoked |Resolve|
  std::optional<bool> IsSatisfied() const;

  // check the promise has invoked |Reject|
  std::optional<bool> IsUnsatisfied() const;

  bool IsExpired() const { return ptr_.expired(); }

  PromiseResolver() : ptr_() {}

protected:
  explicit PromiseResolver(const std::shared_ptr<_::PromiseState<T>> &p)
      : ptr_(p) {}

private:
  std::weak_ptr<_::PromiseState<T>> ptr_;

  template <typename U> friend class Promise;
};

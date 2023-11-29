#pragma once
#include <cstdint>

enum class PromiseStatus : std::uint8_t {
  // initial state
  kInit,
  // pre-fulfilled, pending state, its callback will be invoked
  kPreFulfilled,
  // fulfilled, its callback has already been invoked in executor
  kFulfilled,
  // pre-rejected state, pending state. its callback will be invoked
  kPreRejected,
  // rejected, its callback has already been invoked in executor
  kRejected,
  // cancalled, its callback and storage has been purged
  kCancelled,
};

class PromiseStatusMachine {
public:
  PromiseStatusMachine() = default;

  PromiseStatus status() const { return status_; }

  bool IsEmpty() const { return status() == PromiseStatus::kInit; }
  bool IsPreFulfilled() const {
    return status() == PromiseStatus::kPreFulfilled;
  }
  bool IsFulfilled() const { return status() == PromiseStatus::kFulfilled; }
  bool IsPreRejected() const { return status() == PromiseStatus::kPreRejected; }
  bool IsRejected() const { return status() == PromiseStatus::kRejected; }
  bool IsCancelled() const { return status() == PromiseStatus::kCancelled; }

public:
  bool ToPreFulfilled() {
    return To(PromiseStatus::kInit, PromiseStatus::kPreFulfilled);
  }
  bool ToFulfilled() {
    return To(PromiseStatus::kPreFulfilled, PromiseStatus::kFulfilled);
  }
  bool ToPreRejected() {
    return To(PromiseStatus::kInit, PromiseStatus::kPreRejected);
  }
  bool ToRejected() {
    return To(PromiseStatus::kPreRejected, PromiseStatus::kRejected);
  }
  bool ToCancelled() {
    switch (status()) {
    case PromiseStatus::kInit:
    case PromiseStatus::kPreRejected:
    case PromiseStatus::kPreFulfilled:
      status_ = PromiseStatus::kCancelled;
      return true;
    default:
      return false;
    }
  }

  void Force(PromiseStatus s) { status_ = s; }

public:
  // the callback has not been invoked
  bool IsPending() const { return IsPreRejected() || IsPreFulfilled(); }

  // the callback has been invoked in given executor
  bool IsDone() const { return IsFulfilled() || IsRejected(); }

  // the promise has invoked |resolve|
  bool IsSatisfied() const { return IsPreFulfilled() || IsFulfilled(); }

  // the promise has invoked |reject|
  bool IsUnsatisfied() const { return IsPreRejected() || IsRejected(); }

  // the result has been settled
  bool IsSettled() const { return !IsEmpty() && !IsCancelled(); }

private:
  bool To(PromiseStatus from, PromiseStatus to) {
    if (status() == from) {
      status_ = to;
      return true;
    }
    return false;
  }

  PromiseStatus status_{PromiseStatus::kInit};
};

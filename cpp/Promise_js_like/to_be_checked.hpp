#pragma once
// to be CHECKED
#include <cassert>
#include <functional>
#include <string>

#define CHECK(condition) assert(condition)

namespace base {

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
class Pass {
public:
};

} // namespace base
class Executor {
public:
  virtual void Post(std::function<void()> &&handler) {}
};
#define DISALLOW_COPY_AND_ASSIGN(TypeName)                                     \
  TypeName(const TypeName &) = delete;                                         \
  TypeName &operator=(const TypeName &) = delete;

template <typename T> class Result {
public:
  enum class Status {
    kSuccess,
    kFailure
    // Add more status types as needed
  };

  Result(Status status, T &&value)
      : status_(status), value_(std::move(value)) {}

  Status GetStatus() const { return status_; }
  const T &GetValue() const { return value_; }

private:
  Status status_;
  T value_;
};
template <typename> struct IsResult : std::false_type {};

template <typename T> struct IsResult<Result<T>> : std::true_type {};

template <typename> struct IsPromise : std::false_type {};

// template <typename T> struct IsPromise<PromiseState<T>> : std::true_type {};
// check above

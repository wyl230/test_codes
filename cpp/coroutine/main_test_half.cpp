#include <better_print.hpp>
#include <coroutine>
#include <iostream>

struct promise;

struct coroutine : std::coroutine_handle<promise> {
  using promise_type = ::promise;
};

struct promise {
  coroutine get_return_object() { return {coroutine::from_promise(*this)}; }
  std::suspend_always initial_suspend() noexcept { return {}; }
  std::suspend_always final_suspend() noexcept { return {}; }
  void return_void() {}
  void unhandled_exception() {}
};

struct S {
  int i;
  coroutine f() {
    std::cout << i;
    co_return;
  }
};

void bad1() {
  coroutine h = S{0}.f();
  // S{0} destroyed
  h.resume(); // resumed coroutine executes std::cout << i, uses S::i after free
  h.destroy();
}

coroutine bad2() {
  S s{0};
  return s.f(); // returned coroutine can't be resumed without committing use
                // after free
}

void bad3() {
  coroutine h = [i = 0]() -> coroutine // a lambda that's also a coroutine
  {
    std::cout << i;
    co_return;
  }(); // immediately invoked
  // lambda destroyed
  h.resume(); // uses (anonymous lambda type)::i after free
  h.destroy();
}

void good() {
  coroutine h = [](int i) -> coroutine // make i a coroutine parameter
  {
    print(i);
    co_return;
    print(i++);
    co_return;
    print(i++);
    co_return;
    print(i++);
  }(0);
  // lambda destroyed
  h.resume(); // no problem, i has been copied to the coroutine
  h.destroy();
  print("destroy ok");
}

int main(int argc, char *argv[]) {
  print("run ok");
  good();
  // bad1();

  return 0;
}


#include <better_print.hpp>
#include <future>

template <typename T> struct PromiseFutureWrapper {
  std::promise<T> prom;
  std::future<T> fut = prom.get_future();
  T get() {
    T res = fut.get();
    reset();
    return res;
  }
  void reset() {
    prom = std::promise<T>();
    fut = prom.get_future();
  }
};

void some() { std::this_thread::sleep_for(std::chrono::seconds(1)); }

void test() {
  std::promise<int> promise;
  std::future<int> future = promise.get_future();
  // std::thread t(print_int, std::ref(fut));
  promise.set_value(23);
  int routes = future.get();
  print(routes);
}

void once(PromiseFutureWrapper<int> &t, int i) {
  t.prom.set_value(i);

  int got = t.get();

  print("got", got);
}

int main(int, char *[]) {

  PromiseFutureWrapper<int> t;
  for (int i = 0; i < 10; ++i)
    once(t, i);

  return 0;
}

//
// // promise example
// #include <functional> // std::ref
// #include <future>     // std::promise, std::future
// #include <iostream>   // std::cout
// #include <thread>     // std::thread
//
// void print_int(std::future<int> &fut) {
//   int x = fut.get();
//   std::cout << "value: " << x << '\n';
// }
//
// int main() {
//   std::promise<int> prom; // create promise
//
//   std::future<int> fut = prom.get_future(); // engagement with future
//
//   std::thread th1(print_int, std::ref(fut)); // send future to new thread
//
//   prom.set_value(10); // fulfill promise
//                       // (synchronizes with getting the future)
//   th1.join();
//   return 0;
// }

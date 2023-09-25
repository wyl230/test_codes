#include "a.cpp"
#include <future>
#include <thread>
#include <vector>

template <typename T> T parallel_accumulate() {

  unsigned long const num_threads = 4;
  std::vector<std::future<T>> futures(num_threads);
  thread_pool pool;

  for (unsigned long i = 0; i < (num_threads); ++i) {
    futures[i] = pool.submit([]() {
      print("emm", "");
      return 12;
    });
  }
  T result = 0;
  for (unsigned long i = 0; i < (num_threads); ++i) {
    result += futures[i].get();
  }
  return result;
}

int main(int argc, char *argv[]) {
  parallel_accumulate<int>();
  return 0;
}

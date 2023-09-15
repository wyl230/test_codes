#include "better_print.cpp"
#include <atomic>
#include <condition_variable>
#include <deque>
#include <functional>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

using namespace std::literals::chrono_literals;

// 最后线程池变量析构之前，先析构joiner，joiner会自动调用join方法
struct join_threads {
  int cnt = 0;
  std::vector<std::thread> &threads;
  explicit join_threads(std::vector<std::thread> &threads) : threads(threads) {}
  ~join_threads() {
    print("joining");
    for (auto &t : threads) {
      t.join();
      print("joined ", ++cnt);
    }
  }
};

template <typename T> class thread_safe_queue {
  std::deque<T> queue;
  std::mutex mutex;
  std::condition_variable condition;

public:
  bool try_pop(T &val) {
    std::unique_lock<std::mutex> lock(mutex);
    // condition.wait(lock, [this] { return !queue.empty(); });
    if (queue.empty()) {
      return false;
    }
    val = queue.front();
    queue.pop_front();
    return true;
  }

  void pop() {
    std::unique_lock<std::mutex> lock(mutex);
    condition.wait(lock, [this] { return !queue.empty(); });
    queue.pop_front();
    print("popped.");
  }

  bool empty() {
    std::lock_guard<std::mutex> lock(mutex);
    return queue.empty();
  }

  void push(T const &val) {
    std::lock_guard<std::mutex> lock(mutex);
    print("pushing: ");
    queue.push_back(val);
    print("pushed.");
  }
};

class thread_pool {
  std::atomic_bool done;
  thread_safe_queue<std::function<void()>> work_queue;
  std::vector<std::thread> threads;
  join_threads joiner;
  std::atomic_uint32_t thread_finished = {0};
  std::mutex mutex;

  void worker_thread() {
    while (!done) {
      std::function<void()> task;
      if (work_queue.try_pop(task)) {
        task();
      } else {
        std::this_thread::yield();
      }
    }
    std::lock_guard<std::mutex> lock(mutex);
    print("worker thread done", ++thread_finished);
  }

  unsigned thread_count = 4;

public:
  thread_pool() : done(false), joiner(threads) {
    // unsigned const thread_count = std::thread::hardware_concurrency();
    print("thread count: ", thread_count);

    try {
      for (unsigned i = 0; i < thread_count; ++i) {
        threads.push_back(std::thread(&thread_pool::worker_thread, this));
        print("pushed thread ", i);
      }
    } catch (...) {
      done = true;
      throw;
    }
  }

  ~thread_pool() {
    print("destroying thread pool...");

    while (!done)
      done = true;
    // std::this_thread::sleep_for(10s);
    while (thread_finished < thread_count)
      ;
  }

  template <typename FunctionType> void submit(FunctionType f) {
    print("submitting...");
    work_queue.push(std::function<void()>(f));
    print("submitted");
  }
};

int main(int argc, char *argv[]) {
  thread_pool pool;
  for (int i = 0; i < 10; ++i) {
    pool.submit([i = i] { print(i, "here"); });
  }
  // pool.submit([] { std::cout << "3" << std::endl; });
  // pool.submit([] { std::cout << "4" << std::endl; });
  // pool.submit([] { std::cout << "5" << std::endl; });
  return 0;
}

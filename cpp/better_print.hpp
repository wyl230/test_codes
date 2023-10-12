
#include <iomanip>
#include <iostream>
#include <mutex>
#include <thread>

// write a template function to print anything
template <typename T> void print(const T &t) { std::cout << t << std::endl; }

template <typename T, typename... Args>
void print(const T &t, const Args &...args) {
  std::cout << t << " ";
  print(args...);
}

static auto const now = std::chrono::steady_clock::now;
static auto const start = now();

using namespace std::chrono_literals;

static void trace(auto const &...args) {
  static std::mutex mx;

  std::lock_guard lk(mx);
  std::cout << std::setw(8) << (now() - start) / 1ms << " ms: ";
  (std::cout << ... << args) << std::endl;
}

static void trace_us(auto const &...args) {
  static std::mutex mx;

  std::lock_guard lk(mx);
  std::cout << std::setw(8) << (now() - start) / 1us << " us: ";
  (std::cout << ... << args) << std::endl;
}

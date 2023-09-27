#include <better_print.hpp>
#include <functional>
#include <future>
#include <thread>
#include <time_cal_using_decorators.hpp>
#include <utility>
#include <vector>
using namespace std;
struct Reading {
  int day;
};

int f() {
  // this_thread::sleep_for(std::chrono::seconds(1));
  return -1;
}

void process_readings_async(const vector<Reading> &surface_readings) {
  auto h1 = async(launch::async, f);
  print(h1.get());
}

void process_readings_plain(const vector<Reading> &surface_readings) {
  print(f());
}

void process_readings_threads(const vector<Reading> &surface_readings) {
  std::thread([]() { print(f()); }).join();
}

int main(int argc, char *argv[]) {
  // exclaim<decltype(process_readings)>(process_readings(vector<Reading>(10)));
  exclaim([]() { process_readings_async(vector<Reading>(10)); }, "async");

  exclaim([]() { process_readings_plain(vector<Reading>(10)); }, "plain");

  exclaim([]() { process_readings_threads(vector<Reading>(10)); }, "thread");
  return 0;
}

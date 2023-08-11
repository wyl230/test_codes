
#include "time_cal_using_decorators.hpp"
#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;
void cp(int n) {
  std::vector<int> v(n, 123);
  exclaim([=]() {
    cout << "cp: ";
    auto new_v = v; // copy
  });
  // cout << v.size() << " " << new_v.size() << endl;
}

void mv(int n) {
  std::vector<int> v(n, 123);
  exclaim([=]() {
    cout << "mv: ";
    auto new_v = std::move(v); // move
  });
  // cout << v.size() << " " << new_v.size() << endl;
}

void test(int n) {
  std::cout << n << std::endl;
  puts("cp: ");
  exclaim([=]() { cp(n); });
  puts("mv: ");
  exclaim([=]() { mv(n); });
}

int main(int argc, char *argv[]) {
  int n = 10000000;
  test(n);
  return 0;
}

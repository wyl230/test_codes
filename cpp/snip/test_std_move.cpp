
#include <better_print.hpp>

struct A {
  A() { print("A::A()"); }
};

void f(A a) {}

int main(int, char *[]) {
  A a;
  f(a);
  return 0;
}

#include <better_print.hpp>
#include <time_cal_using_decorators.hpp>
#include <vector>

void f(std::vector<int> v) { print(v.size()); }
void g(std::vector<int> &&v) { print(v.size(), v[9999]); }

int main(int, char *[]) {
  std::vector<int> v(10000000, 2);
  exclaim([&v]() { f(v); }, "f");

  // exclaim([&v]() { f(std::move(v)); }, "f move");
  exclaim([&v]() { g(std::move(v)); }, "g move");
  return 0;
}

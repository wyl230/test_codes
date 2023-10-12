
#include <better_print.hpp>
#include <cassert>
#include <thread>
#include <vector>
struct Test {
  std::vector<int> v1;
  std::vector<int> v2;
};

int main(int argc, char *argv[]) {
  Test t;
  std::thread f1([&t]() {
    // do something
    for (int i = 0; i < 1000000; i++) {
      t.v1.push_back(i);
    }
  });

  std::thread f2([&t]() {
    // do something
    for (int i = 0; i < 1000000; i++) {
      t.v2.push_back(i);
    }
  });

  f1.join();
  f2.join();
  print(t.v1.size(), t.v2.size());
  assert(t.v1.size() == t.v2.size());

  return 0;
}

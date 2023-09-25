
#include <iostream>
#include <vector>

void test1() {
  std::vector<int> v;
  for (int i = 0; i < 100000; ++i) {
    v.push_back(i);
  }
}

int main(int argc, char *argv[]) {
  test1();
  return 0;
}


// map会自动初始化
#include <better_print.hpp>
#include <unordered_map>

struct M {
  M() { print("M init"); }
};

int main(int argc, char *argv[]) {
  std::unordered_map<int, M> m;
  m[1];
  return 0;
}

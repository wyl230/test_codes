
#include "better_print.hpp"
#include <fstream>
#include <nlohmann/json.hpp>
#include <string>
// 测试类
class Test {
public:
  std::string s = "Fuxk Cpp.";

  Test() { std::cout << "\tctor\n"; }
  ~Test() { std::cout << "\tdtor\n"; }
  Test(const Test &) { std::cout << "\tcopy ctor\n"; }
  Test(Test &&) noexcept { std::cout << "\tmove ctor\n"; }
  Test &operator=(const Test &) {
    std::cout << "\tcopy op= \n";
    return *this;
  }
  Test &operator=(Test &&) noexcept {
    std::cout << "\tmove op= \n";
    return *this;
  }
};

// 测试函数
void OptFunc(std::optional<Test> x) { print(x->s); }
void DefaultFunc(const Test &x) { print(x.s); }
// 测试代码
int main() {
  Test t0;
  std::cout << "-----------------------------------------\n";
  std::cout << "Use Optional:\n";
  std::cout << "copy:\n";

  OptFunc(t0);
  std::cout << "-------------\n";
  std::cout << "move:\n";

  OptFunc(Test());
  std::cout << "-----------------------------------------\n";
  std::cout << "Not use Optional:\n";
  std::cout << "copy:\n";

  DefaultFunc(t0);
  std::cout << "-----------------\n";
  std::cout << "move:\n";

  DefaultFunc(Test());
  std::cout << "-----------------------------------------\n";

  return 0;
}

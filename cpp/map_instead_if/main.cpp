
#include <functional>
#include <print.hpp>
#include <string>
#include <unordered_map>

class Test {
public:
  void f1() { std::cout << "f1" << std::endl; }
  void f2() { std::cout << "f2" << std::endl; }

  std::unordered_map<std::string, std::function<void()>> m{
      {"f1", std::function<void()>(f1)}, {"f2", std::function<void()>(f2)}};
};

int main() {
  Test test;
  // 调用 f1
  test.m["f1"]();
  // 调用 f2
  test.m["f2"]();

  return 0;
}

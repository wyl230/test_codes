
#include <better_print.hpp>
struct Func {
  void operator()() { print("function"); }
  Func() { print("hello"); }
  ~Func() { print("goodbye"); }
};

int main(int, char *[]) {
  auto fuc = Func();

  print("should before goodbye");
  return 0;
}

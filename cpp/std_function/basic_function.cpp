
#include <functional>
#include <iostream>

// 示例1：使用std::function调用普通函数
int add(int a, int b) { return a + b; }

int test1() {
  std::function<int(int, int)> func = add;
  int result = func(5, 3);
  std::cout << "示例1结果：" << result << std::endl;
  return 0;
}

// 示例2：使用std::function调用Lambda表达式
int test2() {
  std::function<int(int, int)> func = [](int a, int b) { return a + b; };
  int result = func(5, 3);
  std::cout << "示例2结果：" << result << std::endl;
  return 0;
}

// 示例3：使用std::function调用成员函数
class Calculator {
public:
  int add(int a, int b) { return a + b; }
};

int test3() {
  Calculator calc;
  std::function<int(Calculator &, int, int)> func = &Calculator::add;
  int result = func(calc, 5, 3);
  std::cout << "示例3结果：" << result << std::endl;
  return 0;
}

// 示例4：使用std::function作为函数参数
void performOperation(std::function<int(int, int)> operation, int a, int b) {
  int result = operation(a, b);
  std::cout << "示例4结果：" << result << std::endl;
}

int test4() {
  std::function<int(int, int)> func = [](int a, int b) { return a * b; };
  performOperation(func, 5, 3);
  return 0;
}

int main(int argc, char *argv[]) {
  test1();
  test2();
  test3();
  test4();
  return 0;
}

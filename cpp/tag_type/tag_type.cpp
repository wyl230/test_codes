#include <iostream>

// 空的结构体作为标记类型
struct MyTag {};

// 用于根据标记类型选择不同实现的模板类
template <typename T> class MyTemplateClass;

// 部分特化，处理 MyTag 类型
template <> class MyTemplateClass<MyTag> {
public:
  static void process() {
    std::cout << "Processing based on MyTag type." << std::endl;
  }

  void f() { std::cout << "f" << std::endl; }
};

// 部分特化，处理其他类型
template <typename T> class MyTemplateClass {
public:
  static void process() {
    std::cout << "Processing based on other type." << std::endl;
  }
  void f() { std::cout << "f" << std::endl; }
};

int main() {
  // 使用标记类型 MyTag 调用特定的实现
  MyTemplateClass<MyTag>::process();

  // 使用其他类型调用通用的实现
  MyTemplateClass<int>::process();

  return 0;
}

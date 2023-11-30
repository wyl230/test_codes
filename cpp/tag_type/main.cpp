#include <iostream>

// 基类
class MyBaseClass {
public:
  void f() { std::cout << "f" << std::endl; }
};

// 部分特化，处理其他类型
template <typename T> class MyTemplateClass : public MyBaseClass {
public:
  static void process() {
    std::cout << "Processing based on other type." << std::endl;
  }
};

// 部分特化，处理 MyTag 类型
struct MyTag {};
template <> class MyTemplateClass<MyTag> : public MyBaseClass {
public:
  static void process() {
    std::cout << "Processing based on MyTag type." << std::endl;
  }
};

int main() {
  MyTemplateClass<int>::process();
  MyTemplateClass<MyTag>::process();

  MyTemplateClass<int> obj1;
  MyTemplateClass<MyTag> obj2;

  obj1.f(); // 调用基类的 f 函数
  obj2.f(); // 调用基类的 f 函数

  return 0;
}


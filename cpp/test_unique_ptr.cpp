
#include <iostream>
#include <memory>

class MyClass {
public:
  MyClass(int value) : data(value) {}
  void print() { std::cout << "Value: " << data << std::endl; }

private:
  int data;
};

int main() {
  // 创建一个 std::unique_ptr 智能指针
  std::unique_ptr<MyClass> ptr = std::make_unique<MyClass>(42);

  // std::cout << ptr << std::endl;
  // 获取对象的引用
  MyClass &objRef = *ptr;

  // 现在你可以使用 objRef 访问对象的成员函数
  objRef.print();
  std::cout << &objRef << std::endl;

  // 注意：不要在 objRef 存在的同时释放 ptr，否则会导致未定义行为
  // 如果需要释放 ptr，可以在使用完 objRef 后将 ptr 置为空
  ptr.reset();

  return 0;
}

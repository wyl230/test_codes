#include <iostream>

class MyClass {
public:
  MyClass() {
    // 在构造函数中初始化线程局部状态
    thread_local_state = 0;
  }

  void incrementThreadLocalState() {
    // 操作线程局部状态
    thread_local_state++;
  }

  void printThreadLocalState() {
    // 打印线程局部状态的值
    std::cout << "Thread-local state: " << thread_local_state << std::endl;
  }

private:
  static thread_local int thread_local_state; // 全局 thread_local 变量
};

// 初始化 thread_local_state
thread_local int MyClass::thread_local_state = 0;

int main() {
  MyClass obj1;
  MyClass obj2;

  obj1.incrementThreadLocalState();
  obj1.incrementThreadLocalState();
  obj1.incrementThreadLocalState();
  obj1.incrementThreadLocalState();
  obj2.incrementThreadLocalState();
  obj2.incrementThreadLocalState();
  obj2.incrementThreadLocalState();
  obj2.incrementThreadLocalState();
  obj2.incrementThreadLocalState();
  obj2.incrementThreadLocalState();
  obj2.incrementThreadLocalState();
  obj2.incrementThreadLocalState();
  obj2.incrementThreadLocalState();
  obj2.incrementThreadLocalState();
  obj2.incrementThreadLocalState();

  obj1.printThreadLocalState(); // 输出: Thread-local state: 1
  obj2.printThreadLocalState(); // 输出: Thread-local state: 1

  return 0;
}

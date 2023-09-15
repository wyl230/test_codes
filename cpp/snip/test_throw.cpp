
#include <iostream>

// 自定义异常类
class MyException {
public:
  MyException(const std::string &message) : message_(message) {}
  const std::string &what() const { return message_; }

private:
  std::string message_;
};

// 函数，模拟可能抛出异常的操作
void doSomething(int value) {
  if (value < 0) {
    throw MyException("Value cannot be negative");
  }
}

int main() {
  try {
    int userInput;
    std::cout << "Enter a positive number: ";
    std::cin >> userInput;

    doSomething(userInput);

    std::cout << "No exception was thrown." << std::endl;
  } catch (const MyException &e) {
    std::cerr << "Caught exception: " << e.what() << std::endl;
  } catch (...) {
    std::cerr << "Caught an unknown exception." << std::endl;
  }

  return 0;
}

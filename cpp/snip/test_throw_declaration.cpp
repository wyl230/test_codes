
#include <iostream>
#include <stdexcept>

// 函数声明，声明了可能抛出两种异常类型
void divide(int numerator, int denominator) throw(std::invalid_argument,
                                                  std::runtime_error);

int main() {
  int num, denom;
  std::cout << "Enter numerator: ";
  std::cin >> num;
  std::cout << "Enter denominator: ";
  std::cin >> denom;

  try {
    divide(num, denom);
    std::cout << "Result: " << num / denom << std::endl;
  } catch (const std::invalid_argument &e) {
    std::cerr << "Invalid argument exception: " << e.what() << std::endl;
  } catch (const std::runtime_error &e) {
    std::cerr << "Runtime error exception: " << e.what() << std::endl;
  }

  return 0;
}

// 函数定义，实现了可能抛出的异常类型
void divide(int numerator, int denominator) throw(std::invalid_argument,
                                                  std::runtime_error) {
  if (denominator == 0) {
    throw std::invalid_argument("Denominator cannot be zero");
  } else if (numerator < 0 || denominator < 0) {
    throw std::runtime_error(
        "Both numerator and denominator must be non-negative");
  }
  // 执行除法操作
}

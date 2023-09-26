
#include <iostream>

// 定义一个联合体
union MyUnion {
  int intValue;
  double doubleValue;
  char charValue;
};

int main() {
  MyUnion myUnion;

  myUnion.intValue = 42;
  myUnion.doubleValue = 3.141591111111111111111111111111111111111;
  // myUnion.charValue = '1';
  std::cout << sizeof(myUnion) << "myUnion\n";
  std::cout << sizeof(int) << std::endl;
  std::cout << sizeof(double) << std::endl;
  std::cout << sizeof(char) << std::endl;
  // 8 (sizeof(int) + sizeof(double) + sizeof(char)

  std::cout << "intValue: " << myUnion.intValue << std::endl;
  std::cout << "doubleValue: " << myUnion.doubleValue << std::endl;
  std::cout << "charValue: " << myUnion.charValue << std::endl;

  return 0;
}

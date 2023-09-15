
#include <iostream>

void test() {
  // C-style cast
  double d = 3.14;
  int i1 = (int)d;

  // Static cast
  int i2 = static_cast<int>(d);

  // Dynamic cast (used for polymorphic types and classes with virtual
  // functions)
  class Base {
  public:
    virtual ~Base() {}
  };
  class Derived : public Base {};

  Base *basePtr = new Derived;
  Derived *derivedPtr = dynamic_cast<Derived *>(basePtr);
  if (derivedPtr) {
    std::cout << "Dynamic cast successful" << std::endl;
  } else {
    std::cout << "Dynamic cast failed" << std::endl;
  }

  // Const cast
  const int constValue = 42;
  int &nonConstRef = const_cast<int &>(constValue);
  nonConstRef = 23;

  // Reinterpret cast
  int intValue = 65;
  char charValue = static_cast<char>(intValue);

  std::cout << "C-style cast: " << i1 << std::endl;
  std::cout << "Static cast: " << i2 << std::endl;
  std::cout << "Char value after reinterpret cast: " << charValue << std::endl;
}

int main() {
  test();
  return 0;
}

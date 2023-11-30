#include <iostream>
#include <string>
#include <variant>

// 定义一个包含不同类型的 variant
using MyVariant = std::variant<int, double, std::string>;

// 处理 variant 中的不同类型
void processVariant(const MyVariant &var) {

  using T = std::decay_t<decltype(var)>;

  if constexpr (std::is_same_v<T, int>) {
    std::cout << "It's an integer: " << var << std::endl;
  } else if constexpr (std::is_same_v<T, double>) {
    std::cout << "It's a double: " << var << std::endl;
  } else if constexpr (std::is_same_v<T, std::string>) {
    std::cout << "It's a string: " << var << std::endl;
  }
  std::visit(
      [](auto &&arg) {
        using T = std::decay_t<decltype(arg)>;

        if constexpr (std::is_same_v<T, int>) {
          std::cout << "It's an integer: " << arg << std::endl;
        } else if constexpr (std::is_same_v<T, double>) {
          std::cout << "It's a double: " << arg << std::endl;
        } else if constexpr (std::is_same_v<T, std::string>) {
          std::cout << "It's a string: " << arg << std::endl;
        }
      },
      var);
}

int main() {
  MyVariant var1 = 42;
  MyVariant var2 = 3.14;
  MyVariant var3 = "Hello, Variant!";

  processVariant(var1);
  processVariant(var2);
  processVariant(var3);

  return 0;
}

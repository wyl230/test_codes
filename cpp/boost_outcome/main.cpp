
#include <boost/outcome.hpp>
#include <boost/system/result.hpp>
#include <iostream>

boost::outcome_v2::outcome<int, std::string> divide(int numerator,
                                                    int denominator) {
  if (denominator == 0) {
    return std::string("Division by zero");
  }
  return numerator / denominator;
}

int main() {
  int a, b;
  std::cin >> a >> b;
  auto result = divide(a, b);
  if (result) {
    std::cout << "Result: " << result.value() << std::endl;
  } else {
    std::cerr << "Error: " << result.error() << std::endl;
  }
  return 0;
}

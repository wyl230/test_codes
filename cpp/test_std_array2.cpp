
#include <array>
#include <iostream>
#include <valarray>

int main() {
  std::array<char, 1024> arr = {1, 2, 3, 4, 5};

  std::cout << sizeof(arr.data());

  return 0;
}

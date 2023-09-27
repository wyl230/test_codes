#include <cfloat>
#include <cstdint>

// Even more specializations for different types.
// ...
#include <iostream>
#include <limits>

template <typename T> bool greater_than_half_maximum(T value) {
  if (value > std::numeric_limits<T>::max() / 2) {
    return true;
  } else {
    return false;
  }
}

int main(int argc, char *argv[]) {
  std::cout << greater_than_half_maximum<int32_t>(1 << 30);
  return 0;
}

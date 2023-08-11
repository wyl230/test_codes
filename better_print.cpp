
#include <iostream>
#include <thread>

// write a template function to print anything
template <typename T> void print(const T &t) { std::cout << t << std::endl; }

template <typename T, typename... Args>
void print(const T &t, const Args &...args) {
  std::cout << t << " ";
  print(args...);
}

int main(int argc, char *argv[]) {
  print("2234adfaa34", 2, 234, 1.1);
  return 0;
}

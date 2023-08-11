
#include <iostream>
#include <thread>
// test

// write a template function to print anything
template <typename T> void print(const T &t) { std::cout << t << std::endl; }

template <typename T, typename... Args>
void print(const T &t, const Args &...args) {
  std::cout << t << " ";
  print(args...);
}

int main(int argc, char *argv[]) {
  for (int i = 0; i < 3; i++) {
    // print(i, i + 1, i + 2);
    print("2234adfaa34", 2, 234, 1.1);
  }

  // std::cout << "welcome to C++" << std::endl;
  // std::this_thread::sleep_for(std::chrono::seconds(1));
  // std::cout << "welcome to C++" << std::endl;
  // std::this_thread::sleep_for(std::chrono::seconds(1));
  // std::cout << "welcome to C++" << std::endl;
  // std::this_thread::sleep_for(std::chrono::seconds(1));
  // std::cout << "welcome to C++" << std::endl;
  // std::this_thread::sleep_for(std::chrono::seconds(1));
  // std::cout << "welcome to C++" << std::endl;
  return 0;
}

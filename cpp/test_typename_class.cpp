
#include <iostream>

void print() { puts(""); }

template <class Tfirst, class... T> void print(Tfirst f, T... t) {
  std::cout << f << " ";
  print(t...);
}

int main(int argc, char *argv[]) {
  print(1.23, 23, "242qawer");
  print(12, 234);
  return 0;
}

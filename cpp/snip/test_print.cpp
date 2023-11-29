
#include "better_print.hpp"
int main(int argc, char *argv[]) {
  print<"-">("Hello", "World", 42);
  print("Hello", "World", 42);
  return 0;
}

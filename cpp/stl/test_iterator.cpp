
#include "better_print.hpp"
#include <vector>

int main(int argc, char *argv[]) {
  std::vector<int> v;
  for (int i = 0; i < 10; ++i) {
    v.push_back(i);
  }
  std::vector<int>::const_iterator it = std::find(v.begin(), v.end(), 5);
  return 0;
}

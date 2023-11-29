
#include <better_print.hpp>
#include <vector>

int main(int, char *[]) {
  std::vector<int> v;
  for (int i = 0; i < 10; ++i) {
    v.push_back(i);
  }
  std::vector<int>::iterator it =
      std::find_if(v.begin(), v.end(), [](int t) { return t >= 5; });
  for (; it != v.end(); ++it) {
    print(*it);
  }
  return 0;
}

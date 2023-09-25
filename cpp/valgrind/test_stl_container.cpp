
#include <vector>
int main(int argc, char *argv[]) {
  std::vector<int> v;
  for (int i = 0; i < 1000000; i++)
    v.push_back(i);
  return 0;
}

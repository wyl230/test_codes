#include <cstdint>
#include <iostream>
#include <map>
#include <string>
#include <time_cal_using_decorators.hpp>
#include <tsl/robin_map.h>
#include <tsl/robin_set.h>
#include <unordered_map>
#include <vector>

int main(int argc, char *argv[]) {
  exclaim(
      []() {
        std::map<int, std::map<int, int>> m;
        for (int i = 0; i < 3000; ++i) {
          for (int j = 0; j < 3000; ++j) {
            m[i][j] = i + j;
          }
        }
      },
      "map");
  exclaim(
      []() {
        std::unordered_map<int, std::unordered_map<int, int>> m;
        for (int i = 0; i < 3000; ++i) {
          for (int j = 0; j < 3000; ++j) {
            m[i][j] = i + j;
          }
        }
      },
      "unordered");
  exclaim(
      []() {
        std::vector<std::vector<int>> v(3000, std::vector<int>(3000));
        for (int i = 0; i < 3000; ++i) {
          for (int j = 0; j < 3000; ++j) {
            v[i][j] = i + j;
          }
        }
      },
      "vector");
  exclaim(
      []() {
        tsl::robin_map<int, tsl::robin_map<int, int>> m;
        for (int i = 0; i < 3000; ++i) {
          for (int j = 0; j < 3000; ++j) {
            m[i][j] = i + j;
          }
        }
      },
      "robin");
  return 0;
}

// int main() {}

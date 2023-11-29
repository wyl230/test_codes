#include <print.hpp>

struct M {
  M(const M &) = delete;
  M &operator=(const M &) = default;
  M &operator=(M &&) = default;
  M(M &&m) noexcept { print("m move"); }
};
struct Test {
  Test(M &&m) noexcept : m(std::move(m)) { print("t move"); }
  M m;
};

int main(int argc, char *argv[]) { return 0; }

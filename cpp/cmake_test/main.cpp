
#include <better_print.hpp>
#include <functional>
#include <time_cal_using_decorators.hpp>
int main(int argc, char *argv[]) {
  exclaim<std::function<void()>>([argc, argv]() {
    print(argc, argv[0]);
    print("234");
  });

  return 0;
}

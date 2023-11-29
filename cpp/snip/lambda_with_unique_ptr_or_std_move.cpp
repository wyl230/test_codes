#include <iostream>
#include <memory>

void test(std::unique_ptr<int>) {}

int main() {
  // 创建一个std::unique_ptr，包含一个整数
  std::unique_ptr<int> uniquePtr = std::make_unique<int>(42);
  auto p = std::move(uniquePtr);
  auto q = std::move(p);

  test(std::move(q));

  // 将uniquePtr传递到lambda中
  auto lambda = [ptr{std::move(uniquePtr)}]() mutable {
    if (ptr) {
      std::cout << "Value inside lambda: " << *ptr << std::endl;
    } else {
      std::cout << "Value inside lambda is null." << std::endl;
    }
    auto p = std::move(ptr); // need lambda to be mutable
  };

  // 调用lambda
  lambda();

  // 此时uniquePtr为空
  if (!uniquePtr) {
    std::cout << "uniquePtr is null after the lambda call." << std::endl;
  }

  return 0;
}

#include <iostream>
#include <memory>

int main() {
  // 创建一个std::unique_ptr，包含一个整数
  std::unique_ptr<int> uniquePtr = std::make_unique<int>(42);

  // 将uniquePtr传递到lambda中
  auto lambda = [ptr = std::move(uniquePtr)]() {
    if (ptr) {
      std::cout << "Value inside lambda: " << *ptr << std::endl;
    } else {
      std::cout << "Value inside lambda is null." << std::endl;
    }
  };

  // 调用lambda
  lambda();

  // 此时uniquePtr为空
  if (!uniquePtr) {
    std::cout << "uniquePtr is null after the lambda call." << std::endl;
  }

  return 0;
}

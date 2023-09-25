
#include <chrono>
#include <iostream>

int main() {
  // 定义一个时间戳（以秒为单位）
  std::time_t timestamp = 1632282421; // 例如，这是一个时间戳

  // 将时间戳转换为std::chrono::time_point
  std::chrono::system_clock::time_point time_point =
      std::chrono::system_clock::from_time_t(timestamp);

  // 打印结果
  std::cout << "Time Point: "
            << std::chrono::duration_cast<std::chrono::seconds>(
                   time_point.time_since_epoch())
                   .count()
            << " seconds since epoch." << std::endl;

  return 0;
}

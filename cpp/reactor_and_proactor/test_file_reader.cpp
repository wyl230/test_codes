
#include <fstream>
#include <iostream>
#include <string>

int main() {
  std::string filename = "example.txt"; // 替换为你要打开的文件名
  std::ifstream file(filename);

  if (!file.is_open()) {
    std::cerr << "无法打开文件" << filename << std::endl;
    return 1;
  }

  std::string line;
  while (std::getline(file, line)) {
    std::cout << line << std::endl; // 将文件内容逐行输出到终端
  }

  file.close(); // 关闭文件

  return 0;
}

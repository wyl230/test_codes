
#include <stdexcept>
int main(int argc, char *argv[]) {

  throw std::runtime_error("无法打开配置文件");
  return 0;
}

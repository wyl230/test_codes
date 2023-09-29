
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
  const char *filename = "example.txt"; // 替换为你要读取的文件名
  int fd = open(filename, O_RDONLY); // 使用 O_RDONLY 标志以只读模式打开文件

  if (fd == -1) {
    perror("无法打开文件");
    return 1;
  }

  char buffer[1024];
  ssize_t bytesRead;

  while ((bytesRead = read(fd, buffer, sizeof(buffer))) > 0) {
    // 在这里处理读取到的数据
    // 你可以将数据写入到标准输出或进行其他操作
    // 例如：write(STDOUT_FILENO, buffer, bytesRead);
  }

  if (bytesRead == -1) {
    perror("读取文件时出错");
    close(fd);
    return 1;
  }

  close(fd); // 关闭文件

  return 0;
}

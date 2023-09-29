
#include <stdio.h>

int main() {
  const char *filename = "example.txt"; // 替换为你要打开的文件名
  FILE *file = fopen(filename, "r"); // 使用 "r" 模式打开文件（只读模式）

  if (file == NULL) {
    fprintf(stderr, "无法打开文件 %s\n", filename);
    return 1;
  }

  char line[1024]; // 缓冲区用于读取每一行
  while (fgets(line, sizeof(line), file) != NULL) {
    printf("%s", line); // 将文件内容逐行输出到终端
  }

  fclose(file); // 关闭文件

  return 0;
}

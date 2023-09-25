
#include <stdio.h>  // 提供标准输入输出函数
#include <stdlib.h> // 提供标准库函数
#include <string.h> // 提供字符串操作函数
#include <unistd.h> // 提供 getpid() 函数
#include <utility>
const char data_mem[] = "VmRSS:";

/* 打印当前消耗内存 */
inline void print_mem(int pid, const char *func_name) {
  FILE *stream;
  char cache[256];
  char mem_info[64];

  printf("after func:[%-30s]\t", func_name);
  sprintf(mem_info, "/proc/%d/status", pid);
  stream = fopen(mem_info, "r");
  if (stream == NULL) {
    return;
  }

  while (fscanf(stream, "%s", cache) != EOF) {
    if (strncmp(cache, data_mem, sizeof(data_mem)) == 0) {
      if (fscanf(stream, "%s", cache) != EOF) {
        printf("hw memory[%s]<=======\n", cache);
        break;
      }
    }
  }
}

// example
// print_mem(getpid(), "test");

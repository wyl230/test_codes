#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>

int main() {
  int port = 8080; // 你要检测的端口
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);

  if (sockfd == -1) {
    std::cerr << "Error creating socket" << std::endl;
    return 1;
  }

  sockaddr_in serverAddress;
  memset(&serverAddress, 0, sizeof(serverAddress));
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_addr.s_addr = INADDR_ANY;
  serverAddress.sin_port = htons(port);

  if (bind(sockfd, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) ==
      0) {
    std::cout << "Port " << port << " is available" << std::endl;
  } else {
    std::cerr << "Port " << port << " is already in use" << std::endl;
  }

  close(sockfd);
  return 0;
}

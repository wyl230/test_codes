
#include <exception>
struct not_connected_to_server : public std::exception {};

int main(int argc, char *argv[]) {
  throw not_connected_to_server();
  return 0;
}

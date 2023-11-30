#include <my_event_loop/event_loop2.hpp>
// #include <event_loop/event_loop2.hpp>
#include <memory>
#include <print.hpp>
int main(int, char *[]) {
  print("234");
  std::unique_ptr<MessageLoop> loop = std::make_unique<MessageLoop>();
  loop->RunOneTask([]() { print("123"); });

  loop->PostTask([]() { print("ur"); }, Severity::kUrgent);
  loop->PostTask([]() { print("cri"); }, Severity::kCritical);
  loop->PostTask([]() { print("ur"); }, Severity::kUrgent);
  loop->PostTask([]() { print("cri"); }, Severity::kCritical);

  loop->RunTasks();
  return 0;
}

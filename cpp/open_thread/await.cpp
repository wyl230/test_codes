
#include <assert.h>
#include <better_print.hpp>
#include <iostream>
#include <memory>
#include <openthread.h>
#include <stdio.h>

using namespace open;

struct TestData {
  std::string data_;
};

struct Test1Data {
  std::string data;
  OpenSync openSync;
  ~Test1Data() { printf("Test1:~Test1Data\n"); }
};

// 子线程调用
void Test1Thread(OpenThreadMsg &msg) {
  switch (msg.state) {
  case OpenThread::START: // 线程启动的消息
    printf("Test1Thread[%s] START\n", msg.name().c_str());
    OpenThread::Sleep(1000);
    break;
  case OpenThread::RUN: // 线程接收到的消息
                        // 接收主线程的OpenSyncReturn对象，对其唤醒并发消息。
  {
    OpenSyncReturn<TestData, Test1Data> *data =
        msg.edit<OpenSyncReturn<TestData, Test1Data>>();
    if (data) {
      std::shared_ptr<TestData> str = data->get();
      if (str) {
        assert(str->data_ == "Waiting for you!");
      }
      auto sptr = std::shared_ptr<Test1Data>(new Test1Data);
      sptr->data.assign("Of Course,I Still Love You!");
      data->wakeup(sptr);

      // 等待主线程唤醒
      sptr->openSync.await();
    }
    OpenThread::Sleep(1000);
    break;
  }
  case OpenThread::STOP: // 线程退出前的消息
    printf("Test1Thread[%s] STOP\n", msg.name().c_str());
    OpenThread::Sleep(1000);
    break;
  default:
    assert(false);
  }
}

int main() {
  // 指定线程名，并创建。未填函数，线程未启动状态，需要执行start启动
  auto threadRef = OpenThread::Create("Test1Thread");
  threadRef.start(Test1Thread);

  // 给子线程发送消息
  auto msg = std::make_shared<OpenSyncReturn<TestData, Test1Data>>();

  {
    auto data = std::make_shared<TestData>();
    data->data_ = "Waiting for you!";
    msg->put(data);
  }

  threadRef.send(msg);
  // 阻塞主线程，等待子线程唤醒
  auto ret = msg->awaitReturn();
  if (ret) {
    assert(ret->data == "Of Course,I Still Love You!");
    print("Test1====>>:", ret->data);
    // 唤醒子线程的阻塞
    ret->openSync.wakeup();
  }
  // 向子线程发送关闭消息
  threadRef.stop();

  // 等待全部线程退出
  OpenThread::ThreadJoin(threadRef);
  return 0;
}

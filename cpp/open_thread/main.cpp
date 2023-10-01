
#include <assert.h>
#include <iostream>
#include <openthread.h>
#include <stdio.h>
#include <vector>
using namespace open;

// 业务数据结构
struct Product {
  int id_;
  std::string goods_;
  Product() : id_(0) {}
};
class Worker : public OpenThreader {
  // task
  template <class T> struct Task {
    std::shared_ptr<T> data_;
    OpenSync openSync_;
    Task() : data_(0) {}
  };
  // Worker工程线程，提供4个worker线程。
  class Factory {
    const std::vector<Worker *> vectWorker_;

  public:
    Factory()
        : vectWorker_({
              new Worker("Producer1"),
              new Worker("Producer2"),
              new Worker("Producer3"),
              new Worker("Producer4"),
          }) {}
    Worker *getWorker() {
      if (vectWorker_.empty())
        return 0;
      return vectWorker_[std::rand() % vectWorker_.size()];
    }
  };
  static Factory Instance_;
  // Worker
  Worker(const std::string &name) : OpenThreader(name) {
    uid_ = 1;
    start();
  }
  ~Worker() {
    for (size_t i = 0; i < vectTask_.size(); ++i)
      vectTask_[i].openSync_.wakeup();
  }
  // 接收到任务
  virtual void onMsg(OpenThreadMsg &msg) {
    Task<Product> *task = msg.edit<Task<Product>>();
    if (task) {
      vectTask_.push_back(*task);
    }

    // 模拟处理task业务逻辑
    if (rand() % 2 == 0) {
      OpenThread::Sleep(1000);
    }

    // 完成task任务后，就唤醒OpenSync，通知task完成
    for (size_t i = 0; i < vectTask_.size(); ++i) {
      auto &task = vectTask_[i];
      if (task.data_) {
        task.data_->id_ = pid_ + 100 * uid_++;
        task.data_->goods_ =
            name_ + " Dog coin" + std::to_string(task.data_->id_);
      }
      task.openSync_.wakeup();
    }
    vectTask_.clear();
  }
  int uid_;
  std::vector<Task<Product>> vectTask_;

public:
  // 统一对外访问服务接口，
  static bool MakeProduct(std::shared_ptr<Product> &product) {
    // 随机选择一个worker提供服务
    auto worker = Instance_.getWorker();
    if (!worker)
      return false;
    // 给worker创建任务，然后发给worker线程
    auto proto = std::make_shared<Task<Product>>();
    proto->data_ = product;
    bool ret = OpenThread::Send(worker->pid(), proto);
    // 阻塞，等待worker线程完成task，唤醒。
    assert(ret);
    proto->openSync_.await();
    return ret;
  }
};

Worker::Factory Worker::Instance_;

// 子线程调用
void TestThread(OpenThreadMsg &msg) {
  switch (msg.state) {
  case OpenThread::START:
    for (size_t i = 0; i < 100; i++) {
      auto product = std::make_shared<Product>();
      Worker::MakeProduct(product);
      printf("[%s] Recevie Product:%s\n", msg.name().c_str(),
             product->goods_.c_str());
    }
    msg.thread().stop();
    break;
  case OpenThread::STOP:
  case OpenThread::RUN:
    break;
  }
}
int main() {
  // 创建4个子线程
  OpenThread::Create("TestThread1").start(TestThread);

  // OpenThread::Create("TestThread2", TestThread);
  // OpenThread::Create("TestThread3", TestThread);
  // OpenThread::Create("TestThread4", TestThread);

  // 等全部子线程退出
  OpenThread::ThreadJoinAll();
  return 0;
}

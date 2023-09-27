
function* thread() {
  console.log("Thread started");

  // 模拟异步操作，例如网络请求
  yield new Promise((resolve) => {
    setTimeout(() => {
      console.log("Async operation completed");
      resolve();
    }, 2000);
  });

  console.log("Thread finished");
}

// 创建一个线程实例
const myThread = thread();

// 启动线程并执行到第一个 yield 表达式
const result = myThread.next();

console.log("Main thread continues");

// 此时线程进入等待状态，等待异步操作完成

// 当异步操作完成后，手动继续线程的执行
result.value.then(() => {
  myThread.next();
});

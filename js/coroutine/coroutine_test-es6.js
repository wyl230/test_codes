const co = require('co');

// 定义一个异步函数
function asyncFunction(value) {
  return new Promise((resolve) => {
    setTimeout(() => {
      resolve(value);
    }, 1000); // 模拟异步操作
  });
}

// 创建一个协程函数
const myCoroutine = co.wrap(function*() {
  console.log('Start Coroutine');
  const result1 = yield asyncFunction(1);
  console.log('Result 1:', result1);
  const result2 = yield asyncFunction(2);
  console.log('Result 2:', result2);
  console.log('End Coroutine');
});

// 运行协程
myCoroutine()
  .then(() => {
    console.log('Coroutine Finished');
  })
  .catch((error) => {
    console.error('Coroutine Error:', error);
  });

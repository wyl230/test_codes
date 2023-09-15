
// 普通函数
function regularFunction() {
  let count = 0;

  return function() {
    count++;
    console.log(count);
  };
}

const counter1 = regularFunction();
counter1(); // 输出 1
counter1(); // 输出 2

// 闭包
function closureFunction() {
  let count = 0;

  return function() {
    count++;
    console.log(count);
  };
}

const counter2 = closureFunction();
const counter3 = closureFunction();

counter2(); // 输出 1
counter2(); // 输出 2

counter3(); // 输出 1（与counter2相互独立，有各自的闭包）


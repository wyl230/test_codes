var assert = require('assert')

function* demo() {
  var res = yield 10;
  assert(res === 32);
  return 42;
}

var d = demo();
console.log(d.next());
console.log(d.next(32));

// var resA = d.next();
// => {value: 10, done: false}
// var resB = d.next(32);
// => {value: 42, done: true}
//if we call d.next() again it throws an error

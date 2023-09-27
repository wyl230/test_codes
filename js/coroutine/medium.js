// from: https://medium.com/@tjholowaychuk/callbacks-vs-coroutines-174f1fe66127

var fs = require('fs');

const print = (v) => { console.log(v); }


const thread = (fn) => {
  var gen = fn();
  function next(err, res) {
    var ret = gen.next(res);
    if (ret.done) return;
    ret.value(next);
  }

  next();
}

// const read = (path) => (done) => { fs.readFile(path, 'utf8', done); }

// const test_done = (done) => {
//   fs.readFile(path, 'utf8', done);
// }

function test_done(done) {
  print('done')
}


thread(function*() {
  var a = yield read('a');
  var b = yield read('b');
  console.log(a);
  console.log(b);

  var t = yield test_done;
  console.log(t);
});

// print(read('a'))

function read(path) {
  return function(done) {
    fs.readFile(path, 'utf8', done);
  }
}

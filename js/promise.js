
function helloWorld() {
  return new Promise(resolve => {
    setTimeout(() => {
      resolve('Hello World!');
    }, 2000);
  });
}

async function msg() {
  // const msg = await helloWorld();
  // console.log('Message:', msg);
  msg = new Promise(resolve => {
    setTimeout(() => {
      resolve('Hello World!');
    }, 2000);
  });
  console.log('test');
  msg.then(res => { console.log(res); });
  console.log('Message:', msg);
}

msg(); // Mes

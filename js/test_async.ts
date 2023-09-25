// 异步函数示例
async function fetchData(url: string): Promise<string> {
  try {
    const response = await fetch(url);
    if (!response.ok) {
      throw new Error(`Network response was not ok: ${response.status}`);
    }
    const data = await response.text();
    return data;
  } catch (error) {
    console.error('Error fetching data:', error);
    throw error;
  }
}

function sleep(ms: number): Promise<void> {
  return new Promise((resolve) => {
    setTimeout(resolve, ms);
  });
}

async function long_task() {
  await sleep(1000);
  const data = await fetchData('https://www.baidu.com');
  return data;
}

// 使用异步函数
async function main() {
  console.log('start');
  const res = await long_task();
  console.log('end');
  console.log(res);
}

// 调用主函数
main();

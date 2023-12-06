import asyncio


async def display(num):
    await asyncio.sleep(1)
    print(num)


coroutines = [display(num) for num in range(10)]

loop = asyncio.get_event_loop()
loop.run_until_complete(asyncio.wait(coroutines))
loop.close()

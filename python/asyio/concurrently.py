import asyncio
import time


async def say_after(delay, what):
    await asyncio.sleep(delay)
    print(what)


async def example():
    task1 = asyncio.create_task(say_after(1, "hello"))

    task2 = asyncio.create_task(say_after(1, "world"))

    print(f"started at {time.strftime('%X')}")

    # Wait until both tasks are completed (should take
    # around 2 seconds.)
    await task1
    await task2

    print(f"finished at {time.strftime('%X')}")


async def better_example():
    async with asyncio.TaskGroup() as tg:
        tg.create_task(say_after(1, "hello"))
        tg.create_task(say_after(0.99, "world"))

        print(f"started at {time.strftime('%X')}")

    # The await is implicit when the context manager exits.

    print(f"finished at {time.strftime('%X')}")


asyncio.run(better_example())

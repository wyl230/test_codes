import asyncio


async def inner_task(task_name, seconds):
    print(f"{task_name} started")
    await asyncio.sleep(seconds)
    print(f"{task_name} completed after {seconds} seconds")


async def outer_task(id):
    # print("Outer task started")
    # await inner_task("Inner Task 1", 2)
    # await inner_task("Inner Task 2", 3)
    # await inner_task("Inner Task 3", 1)
    # print("Outer task completed")

    tasks = [
        inner_task("Task 1", 2 + id),
        inner_task("Task 2", 4),
        inner_task("Task 3", 1),
    ]

    await asyncio.gather(*tasks)


async def main():
    await outer_task(0)
    await outer_task(1)


if __name__ == "__main__":
    asyncio.run(main())

import asyncio


async def async_task(task_name, seconds):
    print(f"{task_name} started")
    await asyncio.sleep(seconds)
    print(f"{task_name} completed after {seconds} seconds")


async def main():
    tasks = [
        async_task("Task 1", 2),
        async_task("Task 2", 3),
        async_task("Task 3", 1),
    ]

    await asyncio.gather(*tasks)

    # await async_task("Task 2", 4)
    # await async_task("Task 3", 1)


if __name__ == "__main__":
    asyncio.run(main())

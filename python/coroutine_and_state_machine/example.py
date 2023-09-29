# Asyncio Finite State Machine
import asyncio
import time
from random import randint


async def some():
    return 23


async def StartState():
    print("Start State called \n")
    input_value = randint(0, 1)
    t = await some()
    print(f"we get {t}")
    await asyncio.sleep(0.1)
    if input_value == 0:
        result = await State2(input_value)
    else:
        result = await State1(input_value)
    print("Resume of the Transition : \nStart State calling " + result)


async def State1(transition_value):
    outputValue = str("State 1 with transition value = %s \n" % transition_value)
    input_value = randint(0, 1)
    await asyncio.sleep(0.1)
    print("...Evaluating...")
    if input_value == 0:
        result = await State3(input_value)
    else:
        result = await State2(input_value)
    result = "State 1 calling " + result
    return outputValue + str(result)


async def State2(transition_value):
    outputValue = str("State 2 with transition value = %s \n" % transition_value)
    input_value = randint(0, 1)
    await asyncio.sleep(0.1)
    print("...Evaluating...")
    if input_value == 0:
        result = await State1(input_value)
    else:
        result = await State3(input_value)
    result = "State 2 calling " + result
    return outputValue + str(result)


async def State3(transition_value):
    outputValue = str("State 3 with transition value = %s \n" % transition_value)
    input_value = randint(0, 1)
    await asyncio.sleep(0.1)
    print("...Evaluating...")
    if input_value == 0:
        result = await State1(input_value)
    else:
        result = await EndState(input_value)
    result = "State 3 calling " + result
    return outputValue + str(result)


async def EndState(transition_value):
    outputValue = str("End State with transition value = %s \n" % transition_value)
    print("...Stop Computation...")
    return outputValue


async def test():
    print("Finite State Machine simulation with Asyncio Coroutine")
    # start_time = time.time()
    # for i in range(10):
    #     loop = asyncio.get_event_loop()
    #     loop.run_until_complete(StartState())
    #
    # print(time.time() - start_time)

    async with asyncio.TaskGroup() as tg:
        for i in range(1):
            tg.create_task(StartState())

        print(f"started at {time.strftime('%X')}")

    # The await is implicit when the context manager exits.

    print(f"finished at {time.strftime('%X')}")


if __name__ == "__main__":
    start_time = time.time()
    asyncio.run(test())
    print(time.time() - start_time)

def sat_ready():
    for _ in range(2):
        yield False
    yield True


for i in sat_ready():
    print(i)

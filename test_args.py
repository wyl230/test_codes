def test(a, b, c):
    return a, b, c


class Base:
    def __init__(self, a, b, c):
        pass


class Test(Base):
    def __init__(self, a, b, c):
        super().__init__(a, b, c)


if __name__ == "__main__":
    args = (1, 2, 3)
    t = Test(*args)

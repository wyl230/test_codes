class TestWith:
    def __enter__(self):
        print("you get in with")

    def __exit__(self, exc_type, exc_val, exc_tb):
        print(exc_type, exc_val, exc_tb)
        print("you get out")


if __name__ == "__main__":
    test = TestWith()
    with TestWith():
        print("hello")

    print("-----")
    with test:
        print("ob")

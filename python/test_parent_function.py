class Base:
    def print(self):
        print("is base")


class Derived(Base):
    def print(self):
        super().print()
        print("is Derived")


d = Derived()
d.print()

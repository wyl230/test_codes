from pydantic.main import BaseModel, Field
from typing import List
from utils import get_members, camel_to_snake


class Inner(BaseModel):
    c: int = Field(..., title="C")
    d: str = Field(..., title="D")


class Test(BaseModel):
    a: int = Field(..., title="A")
    b: str = Field(..., title="B")
    Inner: List[Inner]


if __name__ == "__main__":
    test = Test(a=1, b="1", Inner=[Inner(c=1, d="1"), Inner(c=2, d="2")])
    test2 = Test(a=1, b="1", Inner=[Inner(c=1, d="1"), Inner(c=2, d="2")])
    for member in get_members(test):
        print("mem: ", member)
        v = getattr(test, member)
        print("v", v)
        setattr(test2, camel_to_snake(member), getattr(test, member))
        value = getattr(test2, camel_to_snake(member))
        print(f"{member}: {value}")

    # print(Test.schema_json(indent=2))

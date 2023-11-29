from pydantic.main import BaseModel
from typing import List


class B(BaseModel):
    b: str


class A(BaseModel):
    a: int
    b: str
    c: B


a = A(a=1, b="2", c=B(b="3"))
print(a)

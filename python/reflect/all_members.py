from utils import get_members, camel_to_snake


class MyClass:
    def __init__(self, name, age):
        self.name = name
        self.age = age

    def say_hello(self):
        print("Hello!")

    def get_age(self):
        return self.age


# 创建一个类的实例
my_instance = MyClass("John", 25)

# 获取类的所有成员
members = get_members(my_instance)
# 输出所有成员
for member in members:
    # 使用 getattr 获取成员的值
    value = getattr(my_instance, member)

    # 打印成员名称和值
    setattr(my_instance, member, member + "value")
    setattr(my_instance, "add", 23)
    value = getattr(my_instance, member)
    print(f"{member}: {value}")


# 示例
camel_string = "camelCaseString"
snake_string = camel_to_snake(camel_string)
print(snake_string)

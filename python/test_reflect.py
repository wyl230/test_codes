class A:
    pass


class MyClass:
    def __init__(self):
        self.my_attribute = A()
        self.my_attribute.q = 11

    def my_method(self):
        return "Hello, World!"


# 创建一个类的对象


def dfs(obj):
    # 使用反射遍历对象的属性和方法
    for new_obj in dir(obj):
        if not new_obj.startswith("__"):  # 忽略双下划线开头的特殊方法
            item_value = getattr(obj, new_obj)
            print(type(item_value))
            print(item_value is object)
            print(new_obj is object)
            print(f"{new_obj}: {item_value}")
            # dfs(new_obj)


obj = MyClass()
dfs(32)

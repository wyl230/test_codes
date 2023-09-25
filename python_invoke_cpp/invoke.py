import ctypes

# 加载动态库
mycpplibrary = ctypes.CDLL("./mylib.so")

# 调用动态库中的函数
mycpplibrary.say_hello()

# 调用动态库中的函数并获取返回值
result = mycpplibrary.add(3, 5)
print("3 + 5 =", result)

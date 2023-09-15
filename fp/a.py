# 闭包
def closure_function():
    count = 0

    def increment_count():
        nonlocal count
        count += 1
        print(count)

    return increment_count


counter3 = closure_function()
counter4 = closure_function()

counter3()  # 输出 1
counter3()  # 输出 2

counter4()  # 输出 1（与counter3相互独立，但它们共享同一个闭包作用域内的变量）

import re

# 示例文本数据
text_data = [
    "Name: John, Age: 30, Score: 95",
    "Name: Alice, Age: 25, Score: 88",
    "Name: Bob, Age: 28, Score: 92",
]

with open("a") as f:
    text_data = f.readlines()
# 创建一个正则表达式来匹配数字
pattern = r"\d+"

# 遍历每行文本数据
for line in text_data:
    # 使用正则表达式搜索数字并返回匹配项列表
    numbers = re.findall(pattern, line)

    # 将提取的数字打印出来
    print(numbers)

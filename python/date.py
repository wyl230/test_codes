import datetime
import pytz  # 请确保安装了pytz库

# 输入字符串表示的时间
input_string = "2006-01-01 00:00:00"

# 将输入字符串解析为datetime对象，假设输入字符串是在本地时区
input_datetime = datetime.datetime.strptime(input_string, "%Y-%m-%d %H:%M:%S")

# 将解析后的datetime对象转换为UTC时间
local_timezone = pytz.timezone("Asia/Chongqing")  # 请替换为您的本地时区
utc_datetime = local_timezone.localize(input_datetime).astimezone(pytz.utc)

print(utc_datetime)
print(int(utc_datetime.timestamp()))

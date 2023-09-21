from datetime import datetime, timezone

# 输入的时间字符串
time_string = "2008-02-02 13:39:48"

# 将时间字符串转换为datetime对象
datetime_obj = datetime.strptime(time_string, "%Y-%m-%d %H:%M:%S")

# 将datetime对象转换为UTC时间
datetime_utc = datetime_obj.replace(tzinfo=timezone.utc)

# 获取UTC时间戳（以秒为单位）
timestamp_utc = datetime_utc.timestamp()

print("UTC时间戳:", timestamp_utc)

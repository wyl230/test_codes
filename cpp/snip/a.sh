#!/bin/bash

# 定义一个函数，用于处理Ctrl+C信号
function on_ctrl_c {
	echo "Ctrl+C 按下，执行另一个命令..."
	# 在这里添加你想要执行的命令
	# 例如：echo "执行其他命令"
	# 最后退出脚本
	exit
}

# 使用trap命令捕获Ctrl+C信号，并调用on_ctrl_c函数
trap on_ctrl_c SIGINT

# 主循环，可以在这里添加你的脚本逻辑
while true; do
	# 在这里执行主要的脚本逻辑
	echo "运行中..."
	sleep 1
done

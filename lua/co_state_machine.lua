-- 定义状态
local state = coroutine.create(function()
	print("Start State")
	for i = 1, 3 do
		print("Processing State", i)
		coroutine.yield()
	end
	print("End State")
end)

-- 函数来触发状态迁移
function TransitionState()
	local status, errorMsg = coroutine.resume(state)
	if not status then
		print("Error:", errorMsg)
	end
end

-- 初始触发状态机
TransitionState()
-- 模拟其他事件
print("Handling other tasks")
TransitionState()
TransitionState()
TransitionState()

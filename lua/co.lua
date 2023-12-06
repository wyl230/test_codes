-- 定义一个简单的任务函数
local function task(name, n)
	for i = 1, n do
		print(name, i)
		coroutine.yield()
	end
end

-- 创建两个协程
local co1 = coroutine.create(function()
	task("Coroutine 1", 5)
end)

local co2 = coroutine.create(function()
	task("Coroutine 2", 3)
end)

-- 执行协程，交替运行
while coroutine.status(co1) == "suspended" or coroutine.status(co2) == "suspended" do
	if coroutine.status(co1) == "suspended" then
		coroutine.resume(co1)
	end

	if coroutine.status(co2) == "suspended" then
		coroutine.resume(co2)
	end
end

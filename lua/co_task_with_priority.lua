-- 任务队列
local taskQueue = {}

-- 添加任务到队列
function addTask(task, priority)
	table.insert(taskQueue, { task = task, priority = priority or 0 })
	table.sort(taskQueue, function(a, b)
		return a.priority > b.priority
	end)
end

-- 任务执行函数
function executeTasks()
	while #taskQueue > 0 do
		local taskItem = table.remove(taskQueue, 1)
		local task = taskItem.task
		coroutine.yield() -- 模拟异步操作

		local status, result = coroutine.resume(task)
		if not status then
			print("Error executing task:", result)
		end
	end
end

-- 创建任务执行协程
taskCoroutine = coroutine.create(executeTasks)

-- 添加一些任务到队列（带有优先级）
addTask(
	coroutine.create(function()
		print("Executing high-priority task 1")
	end),
	3
)

addTask(
	coroutine.create(function()
		print("Executing low-priority task 2")
	end),
	1
)

addTask(
	coroutine.create(function()
		print("Executing medium-priority task 3")
	end),
	2
)

-- 启动任务执行协程
while coroutine.status(taskCoroutine) ~= "dead" do
	coroutine.resume(taskCoroutine)
end

-- 任务队列
local taskQueue = {}

-- 添加任务到队列
function AddTask(task)
	table.insert(taskQueue, task)
end

-- 任务执行函数
function ExecuteTasks()
	while #taskQueue > 0 do
		local task = table.remove(taskQueue, 1)
		coroutine.yield() -- 模拟异步操作
		print("Executing task:", task)
	end
end

-- 创建任务执行协程
TaskCoroutine = coroutine.create(ExecuteTasks)

-- 添加一些任务到队列
--- change int to string

for i = 1, 5 do
	AddTask("Task" .. i)
end

-- 启动任务执行协程
-- for _ = 1, 10 do
local status, value = coroutine.resume(TaskCoroutine)
print("here", status, value)
coroutine.resume(TaskCoroutine)
AddTask("Task")
-- end

-- AddTask("Task 4")
-- AddTask("Task 5")
--
-- coroutine.resume(TaskCoroutine)
-- coroutine.resume(TaskCoroutine)
-- coroutine.resume(TaskCoroutine)
-- coroutine.resume(TaskCoroutine)
-- coroutine.resume(TaskCoroutine)
-- coroutine.resume(TaskCoroutine)
-- coroutine.resume(TaskCoroutine)
-- coroutine.resume(TaskCoroutine)

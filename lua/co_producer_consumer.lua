-- 生产者函数
function Producer()
	for i = 1, 5 do
		print("Producing: " .. i)
		coroutine.yield(i) -- 发送生成的数字给消费者
	end
end

-- 消费者函数
function Consumer()
	while true do
		local status, value = coroutine.resume(ProducerCoroutine)
		if not status or not value then
			break -- 生产者结束，消费者也结束
		end
		print("Consuming: " .. value)
	end
end

-- 创建生产者协程
ProducerCoroutine = coroutine.create(Producer)

-- 创建消费者协程
ConsumerCoroutine = coroutine.create(Consumer)

-- 启动消费者协程
coroutine.resume(ConsumerCoroutine)

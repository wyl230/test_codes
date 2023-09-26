1.  decltype
2.  std::function
3.  async

std::launch::async：表示任务应该立即在线程池中执行。这意味着异步任务会在std::async函数被调用时就立即创建并开始执行，不会延迟到std::future的get函数被调用时。这种方式可以确保异步任务在后台线程中执行。

std::launch::deferred：表示任务应该延迟执行，直到调用std::future的get函数时才开始执行。这种方式可以避免不必要的线程创建和并发执行，直到需要结果时才启动任务。

默认情况下，std::async使用的是std::launch::async | std::launch::deferred，这意味着系统会根据情况自动选择启动策略，可能会根据线程池的可用性和其他因素来决定是否立即执行任务。

为了明确指定启动策略，你可以传递一个参数，如std::launch::async，来告诉std::async如何执行任务。如果你想要确保异步任务在后台线程中立即执行，可以传递std::launch::async作为参数。如果你希望任务延迟执行，只有在调用std::future的get函数时才开始执行，可以传递std::launch::deferred作为参数。

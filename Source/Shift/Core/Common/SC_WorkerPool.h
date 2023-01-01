#pragma once
#include <mutex>
#include <queue>

class SC_Thread;

class SC_WorkerPool
{
private:
	enum TaskType
	{
		FRAME_TASK,
		LONG_TASK,

		TASK_TYPE_COUNT
	};

	class WorkerTaskQueue
	{
	public:
		WorkerTaskQueue();
		~WorkerTaskQueue();

		void AddTask(std::function<void()> aTask);
		bool PopTask(std::function<void()>& aOutTask);

		SC_Event mHasTasksEvent;
		std::mutex mMutex;
		std::queue<std::function<void()>> mQueue;
	};

	class WorkerThread final : public SC_Thread 
	{
	public:
		WorkerThread() : mTaskQueue(nullptr) {}
		WorkerThread(WorkerThread&&) = default;
		~WorkerThread() {}

		void SetTaskQueue(WorkerTaskQueue* aTaskQueue) { mTaskQueue = aTaskQueue; }

	protected:
		void ThreadMain() override;

		WorkerTaskQueue* mTaskQueue;
	};

public:
	static bool Init(int32 aNumFrameTaskWorkers = -1, int32 aNumLongTaskWorkers = -1);
	static void Shutdown();

	static void SubmitTask(std::function<void()> aTask, bool aIsLongTask);

	static uint32 GetFrameTaskWorkerCount();
	static uint32 GetLongTaskWorkerCount();

private:
	SC_WorkerPool();
	~SC_WorkerPool();

	bool InitInternal(int32 aNumFrameTaskWorkers, int32 aNumLongTaskWorkers);

	SC_Array<WorkerThread> mTaskWorkers[TASK_TYPE_COUNT];
	WorkerTaskQueue mTaskQueues[TASK_TYPE_COUNT];

	static SC_WorkerPool* gInstance;
};

template <class Func, class... Args, class ReturnType = std::invoke_result_t<std::decay_t<Func>, std::decay_t<Args>...>>
SC_Future<ReturnType> SC_CreateFrameTask(Func&& aFunction, Args&&... aArgs)
{
	SC_Promise<ReturnType>* promise = new SC_Promise<ReturnType>();
	SC_Future<ReturnType> future = promise->GetFuture();
	
	auto task = [aFunction, aArgs..., promise]()
	{ 
		if constexpr (std::is_void_v<ReturnType>)
		{
			aFunction(aArgs...);
			promise->SetValue();
		}
		else
		{
			promise->SetValue(aFunction(aArgs...));
		}
		delete promise;
	};

	SC_WorkerPool::SubmitTask(task, false);

	return future;
}
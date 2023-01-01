#include "Common_Precompiled.h"
#include "SC_WorkerPool.h"

SC_WorkerPool::WorkerTaskQueue::WorkerTaskQueue()
{

}

SC_WorkerPool::WorkerTaskQueue::~WorkerTaskQueue()
{

}

void SC_WorkerPool::WorkerTaskQueue::AddTask(std::function<void()> aTask)
{
	{
		std::unique_lock<std::mutex> lock(mMutex);
		mQueue.push(aTask);
	}

	mHasTasksEvent.Signal();
}

bool SC_WorkerPool::WorkerTaskQueue::PopTask(std::function<void()>& aOutTask)
{
	if (mQueue.empty())
		return false;

	std::unique_lock<std::mutex> lock(mMutex);
	if (mQueue.empty())
		return false;

	aOutTask = mQueue.front();
	mQueue.pop();
	return true;
}

void SC_WorkerPool::WorkerThread::ThreadMain()
{
	while (mIsActive)
	{
		mTaskQueue->mHasTasksEvent.Wait();
		mTaskQueue->mHasTasksEvent.Reset();

		std::function<void()> task;
		while (mTaskQueue->PopTask(task))
		{
			task();
		}
	}
}

SC_WorkerPool* SC_WorkerPool::gInstance = nullptr;

bool SC_WorkerPool::Init(int32 aNumFrameTaskWorkers, int32 aNumLongTaskWorkers)
{
	if (!gInstance)
		gInstance = new SC_WorkerPool();

	if (!gInstance->InitInternal(aNumFrameTaskWorkers, aNumLongTaskWorkers))
		return false;

	return true;
}

void SC_WorkerPool::SubmitTask(std::function<void()> aTask, bool aIsLongTask)
{
	if (!gInstance)
		return;

	gInstance->mTaskQueues[aIsLongTask ? LONG_TASK : FRAME_TASK].AddTask(aTask);
}

void SC_WorkerPool::Shutdown()
{
	delete gInstance;
	gInstance = nullptr;
}

uint32 SC_WorkerPool::GetFrameTaskWorkerCount()
{
	return gInstance->mTaskWorkers[FRAME_TASK].Count();
}

uint32 SC_WorkerPool::GetLongTaskWorkerCount()
{
	return gInstance->mTaskWorkers[LONG_TASK].Count();
}

SC_WorkerPool::SC_WorkerPool()
{

}

SC_WorkerPool::~SC_WorkerPool()
{

}

bool SC_WorkerPool::InitInternal(int32 aNumFrameTaskWorkers, int32 aNumLongTaskWorkers)
{
	int32 counts[2] = { aNumFrameTaskWorkers, aNumLongTaskWorkers };
	for (uint32 type = 0; type < 2; ++type)
	{
		SC_Array<WorkerThread>& taskWorkers = mTaskWorkers[type];
		uint32 numWorkers = counts[type];
		if (numWorkers == -1)
			numWorkers = SC_Clamp((int32)SC_Thread::GetMaxHardwareConcurrency() - 1, 2, (int32)SC_Thread::GetOSThreadLimit());

		taskWorkers.Respace(numWorkers);
		for (uint32 i = 0; i < numWorkers; ++i)
		{
			WorkerThread& worker = taskWorkers[i];
			worker.SetTaskQueue(&mTaskQueues[type]);
			worker.SetName(SC_FormatStr((type == FRAME_TASK) ? "Frame Task {}" : "Long Task {}", i).c_str());
			worker.Start();
		}
	}

	return true;
}

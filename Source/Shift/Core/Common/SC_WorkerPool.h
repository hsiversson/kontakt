#pragma once

class SC_WorkerPool
{
public:
	static bool Create();
	static void Destroy();
	static SC_WorkerPool* Get();

private:
	SC_WorkerPool();
	~SC_WorkerPool();

	SC_Array<SC_Thread> mTaskThreads;
	SC_Array<SC_Thread> mLongTaskThreads;

	static SC_WorkerPool* gInstance;
};

//template<class Fn>
//auto SC_StartTask(Fn&& aFunction) -> SC_Future<decltype(aFunction())>
//{
//
//}


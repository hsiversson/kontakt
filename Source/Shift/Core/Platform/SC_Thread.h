//ProjectFilter(Async)
#pragma once
#include <thread>
#include <string>
#include <functional>

#include "SC_Semaphore.h"
#include "SC_Mutex.h"

#ifdef Yield
#undef Yield
#endif

using SC_ThreadId = std::thread::id;

class SC_Thread
{
public:
	SC_Thread();
	virtual ~SC_Thread();

	SC_Thread(SC_Thread&&) = default;

	SC_Thread(const SC_Thread&) = delete;
	void operator=(const SC_Thread&) = delete;

	void Start();
	void Stop(bool aBlock = false);
	void WaitFor();

	void SetName(const char* aName);
	const char* GetName() const;

	SC_Semaphore& GetSemaphore();

	static void Yield();
	static void Sleep(uint32 aMilliseconds);

	static void RegisterMainThread();
	static SC_ThreadId GetMainThreadId();
	static SC_ThreadId GetCurrentThreadId();

	static SC_Thread* GetCurrentThread();
	static const char* GetCurrentThreadName();

	static uint32 GetMaxHardwareConcurrency();
	static uint32 GetOSThreadLimit();

protected:
	static uint32 __stdcall ThreadStarterFunc(void* aThread);
	virtual void ThreadMain();

	std::thread mThread;
	std::string mName;
	SC_Semaphore mSemaphore;
	bool mIsActive;

	static thread_local SC_Thread* gCurrentThread;
};


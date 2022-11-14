//ProjectFilter(Async)
#pragma once
#include <thread>
#include <string>

using SC_ThreadId = std::thread::id;

class SC_Thread
{
public:
	SC_Thread();
	~SC_Thread();

	SC_Thread(const SC_Thread&) = delete;
	void operator=(const SC_Thread&) = delete;

	void SetName(const char* aName);
	const char* GetName() const;

	static void RegisterMainThread();
	static SC_ThreadId GetMainThreadId();
	static SC_ThreadId GetCurrentThreadId();

	static SC_Thread* GetCurrentThread();
	static const char* GetCurrentThreadName();
private:
	std::thread mThread;
	std::string mName;
	
	static thread_local SC_Thread* gCurrentThread;
};


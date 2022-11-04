#include "Platform_Precompiled.h"
#include "SC_Thread.h"

thread_local SC_Thread* SC_Thread::gCurrentThread = nullptr;

SC_Thread::SC_Thread()
{
}

SC_Thread::~SC_Thread()
{
}

static SC_ThreadId gMainThreadId;
void SC_Thread::SetName(const char* aName)
{
}

const char* SC_Thread::GetName() const
{
	return nullptr;
}

void SC_Thread::RegisterMainThread()
{
	if (gMainThreadId == SC_ThreadId())
		gMainThreadId = std::this_thread::get_id();
}

SC_ThreadId SC_Thread::GetMainThreadId()
{
	return gMainThreadId;
}

SC_ThreadId SC_Thread::GetCurrentThreadId()
{
	return std::this_thread::get_id();
}

SC_Thread* SC_Thread::GetCurrentThread()
{
	return gCurrentThread;
}

const char* SC_Thread::GetCurrentThreadName()
{
	return gCurrentThread->GetName();
}

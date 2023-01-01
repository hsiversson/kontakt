//ProjectFilter(Async)
#include "Platform_Precompiled.h"
#include "SC_Thread.h"

#include <codecvt>

thread_local SC_Thread* SC_Thread::gCurrentThread = nullptr;
static SC_ThreadId gMainThreadId;

SC_Thread::SC_Thread()
	: mThread()
	, mName("<unnamed>")
	, mIsActive(false)
{
}

SC_Thread::~SC_Thread()
{
	Stop();
}

void SC_Thread::Start()
{
	mThread = std::thread(&SC_Thread::ThreadStarterFunc, this);
	mIsActive = true;
}

void SC_Thread::Stop(bool aBlock)
{
	mIsActive = false;
	if (aBlock)
		WaitFor();
}

void SC_Thread::WaitFor()
{
	if (mThread.joinable())
		mThread.join();
}

void SC_Thread::SetName(const char* aName)
{
	mName = aName;
}

const char* SC_Thread::GetName() const
{
	return mName.data();
}

SC_Semaphore& SC_Thread::GetSemaphore()
{
	static SC_Semaphore mainThreadSemaphore;
	return (GetMainThreadId() == GetCurrentThreadId()) ? mainThreadSemaphore : mSemaphore;
}

void SC_Thread::Yield()
{
	std::this_thread::yield();
}

void SC_Thread::Sleep(uint32 aMilliseconds)
{
	if (aMilliseconds == 0)
		Yield();
	else
		std::this_thread::sleep_for(std::chrono::milliseconds(aMilliseconds));
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

uint32 SC_Thread::GetMaxHardwareConcurrency()
{
	return static_cast<uint32>(std::thread::hardware_concurrency());
}

uint32 SC_Thread::GetOSThreadLimit()
{
#if IS_PC_PLATFORM
	return 128;
#elif IS_LINUX_PLATFORM
	return 128;
#endif
}

uint32 __stdcall SC_Thread::ThreadStarterFunc(void* aThread)
{
	SC_Thread* thread = reinterpret_cast<SC_Thread*>(aThread);
	SC_Thread::gCurrentThread = thread;

	std::wstring wname = SC_UTF::ToUTF16(thread->mName);
#if IS_WINDOWS_PLATFORM
	SetThreadDescription(static_cast<HANDLE>(thread->mThread.native_handle()), wname.data());
#elif IS_LINUX_PLATFORM

#else
#error Platform not supported!
#endif

	{
		uint32 seed = uint32(uint64(time(0)) + uint64(thread));
		srand(seed);
		thread->ThreadMain();
	}

	thread->mIsActive = false;
	SC_Thread::gCurrentThread = nullptr;
	return 0;
}

void SC_Thread::ThreadMain()
{
}

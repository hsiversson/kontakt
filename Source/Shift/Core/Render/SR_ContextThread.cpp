//ProjectFilter(Interface)
#include "Render_Precompiled.h"
#include "SR_ContextThread.h"
#include "SR_RenderContext.h"

SR_ContextThread::SR_ContextThread(const SR_CommandListType& aContextType)
	: mContextType(aContextType)
{

}

SR_ContextThread::~SR_ContextThread()
{
	delete mRenderContext;
	mRenderContext = nullptr;
}

bool SR_ContextThread::Init()
{
	mRenderContext = new SR_RenderContext();
	return true;
}

SC_Ref<SC_Event> SR_ContextThread::PostTask(std::function<void()> aTask)
{
	SC_Ref<SC_Event> event = new SC_Event();

	SC_Event* eventPtr = event;
	eventPtr->IncrementRef();
	auto trackedTask = [aTask, eventPtr]()
	{
		aTask();
		eventPtr->Signal();
		eventPtr->DecrementRef();
	};
	mTaskQueue.AddTask(trackedTask);

	return event;
}

const SR_CommandListType& SR_ContextThread::GetContextType() const
{
	return mContextType;
}

void SR_ContextThread::ThreadMain()
{
	SR_RenderContext::gCurrentContext = mRenderContext;

	while (mIsActive)
	{
		mTaskQueue.mHasTasksEvent.Wait();
		mTaskQueue.mHasTasksEvent.Reset();

		std::function<void()> task;
		while (mTaskQueue.PopTask(task))
		{
			SC_Ref<SR_CommandList> cmdList = SR_RenderDevice::gInstance->CreateCommandList(mContextType);
			mRenderContext->BeginTask(cmdList);
			task();
			mRenderContext->EndTask(true);
		}
	}

	SR_RenderContext::gCurrentContext = nullptr;
}

void SR_ContextThread::TaskQueue::AddTask(std::function<void()> aTask)
{
	{
		std::unique_lock<std::mutex> lock(mMutex);
		mQueue.push(aTask);
	}

	mHasTasksEvent.Signal();
}

bool SR_ContextThread::TaskQueue::PopTask(std::function<void()>& aOutTask)
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

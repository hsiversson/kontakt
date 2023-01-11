//ProjectFilter(Interface)
#pragma once
#include "SC_Thread.h"

class SR_RenderContext;
class SR_ContextThread : public SC_Thread
{
public:
	SR_ContextThread(const SR_CommandListType& aContextType);
	~SR_ContextThread();

	bool Init();

	SC_Ref<SC_Event> PostTask(std::function<void()> aTask);

	const SR_CommandListType& GetContextType() const;

private:
	class TaskQueue
	{
	public:
		void AddTask(std::function<void()> aTask);
		bool PopTask(std::function<void()>& aOutTask);

		SC_Event mHasTasksEvent;
		std::mutex mMutex;
		std::queue<std::function<void()>> mQueue;
	};

private:
	void ThreadMain() override;

	SC_Ptr<SR_RenderContext> mRenderContext;
	TaskQueue mTaskQueue;
	const SR_CommandListType mContextType;
};


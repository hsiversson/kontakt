//ProjectFilter(Interface/CommandList)
#pragma once
#include "SR_Fence.h"
#include "SR_CommandList.h"

class SR_CommandQueue : public SR_Resource
{
public:
	SR_CommandQueue();
	virtual ~SR_CommandQueue();

	virtual bool Init(const SR_CommandListType& /*aType*/, const char* /*aDebugName*/ = nullptr);

	virtual void SubmitCommandList(SR_CommandList* aCmdList, const char* aEventName = nullptr);
	virtual void SubmitCommandLists(SR_CommandList** /*aCmdLists*/, uint32 /*aNumCmdLists*/, const char* /*aEventName*/ = nullptr);

	virtual SR_Fence GetNextFence();

	virtual void SignalFence(const SR_Fence& /*aFence*/);
	virtual void SignalFence(uint64 /*aValue*/, SR_FenceResource* /*aResource*/);
	virtual void InsertWait(const SR_Fence& /*aFence*/);
	virtual void InsertWait(uint64 /*aValue*/, SR_FenceResource* /*aResource*/);

	virtual bool IsFencePending(const SR_Fence& /*aFence*/);
	virtual bool WaitForFence(const SR_Fence& /*aFence*/, bool /*aBlock*/ = true);

	virtual void BeginEvent(const char* /*aName*/);
	virtual void EndEvent();

protected:
	SR_CommandListType mType;
};


//ProjectFilter(Interface/CommandList)
#include "Render_Precompiled.h"
#include "SR_CommandQueue.h"

SR_CommandQueue::SR_CommandQueue()
{

}

SR_CommandQueue::~SR_CommandQueue()
{

}

bool SR_CommandQueue::Init(const SR_CommandListType& /*aType*/, const char* /*aDebugName*/ /*= nullptr*/)
{
	return true;
}

void SR_CommandQueue::SubmitCommandLists(SR_CommandList** /*aCmdLists*/, uint32 /*aNumCmdLists*/, const char* /*aEventName*/ /*= nullptr*/)
{

}

SR_Fence SR_CommandQueue::GetNextFence()
{
	return SR_Fence();
}

void SR_CommandQueue::SignalFence(const SR_Fence& /*aFence*/)
{

}

void SR_CommandQueue::InsertWait(const SR_Fence& /*aFence*/)
{

}

bool SR_CommandQueue::IsFencePending(const SR_Fence& /*aFence*/)
{
	return false;
}

bool SR_CommandQueue::WaitForFence(const SR_Fence& /*aFence*/, bool /*aBlock*/ /*= true*/)
{
	return true;
}

void SR_CommandQueue::BeginEvent(const char* /*aName*/)
{

}

void SR_CommandQueue::EndEvent()
{

}

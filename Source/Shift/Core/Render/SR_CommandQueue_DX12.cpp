//ProjectFilter(DX12/CommandList)
#include "Render_Precompiled.h"

#if SR_ENABLE_DX12
#include "SR_CommandQueue_DX12.h"
#include "SR_RenderDevice_DX12.h"
#include "SR_Fence_DX12.h"

SR_CommandQueue_DX12::SR_CommandQueue_DX12()
{

}

SR_CommandQueue_DX12::~SR_CommandQueue_DX12()
{

}

bool SR_CommandQueue_DX12::Init(const SR_CommandListType& aType, const char* aDebugName)
{
	D3D12_COMMAND_QUEUE_DESC desc = {};
	desc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
	desc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
	desc.NodeMask = 0;

	switch (aType)
	{
	case SR_CommandListType::Copy:
		desc.Type = D3D12_COMMAND_LIST_TYPE_COPY;
		break;
	case SR_CommandListType::Compute:
		desc.Type = D3D12_COMMAND_LIST_TYPE_COMPUTE;
		break;
	case SR_CommandListType::Graphics:
	default:
		desc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
		break;
	}

	HRESULT hr = SR_RenderDevice_DX12::gInstance->GetD3D12Device()->CreateCommandQueue(&desc, IID_PPV_ARGS(&mD3D12CommandQueue));
	if (!SR_VerifyHRESULT(hr))
	{
		SC_ASSERT(false, "Could not create command queue.");
		return false;
	}

	mFence = new SR_FenceResource_DX12();
	if (!mFence->Init())
		return false;

	if (aDebugName)
	{
		std::wstring debugName = SC_UTF::ToUTF16(aDebugName);
		mD3D12CommandQueue->SetName(debugName.c_str());
	}

	mType = aType;
	return true;
}

void SR_CommandQueue_DX12::SubmitCommandLists(SR_CommandList** aCmdLists, uint32 aNumCmdLists, const char* aEventName /*= nullptr*/)
{
	if (aEventName)
		BeginEvent(aEventName);

	SC_Array<ID3D12CommandList*> d3d12CmdLists;
	d3d12CmdLists.Reserve(aNumCmdLists);
	for (uint32 i = 0; i < aNumCmdLists; ++i)
	{
		SR_CommandList_DX12* dx12cmdList = static_cast<SR_CommandList_DX12*>(aCmdLists[i]);
		d3d12CmdLists.Add(dx12cmdList->GetD3D12CommandList());
	}

	mD3D12CommandQueue->ExecuteCommandLists(d3d12CmdLists.Count(), d3d12CmdLists.GetBuffer());

	if (aEventName)
		EndEvent();
}

SR_Fence SR_CommandQueue_DX12::GetNextFence()
{
	return SR_Fence(mFence->GetNextValue(), mType);
}

void SR_CommandQueue_DX12::SignalFence(const SR_Fence& aFence)
{
	mD3D12CommandQueue->Signal(mFence->GetD3D12Fence(), aFence.mValue);
}

void SR_CommandQueue_DX12::InsertWait(const SR_Fence& aFence)
{
	mD3D12CommandQueue->Wait(mFence->GetD3D12Fence(), aFence.mValue);
}

bool SR_CommandQueue_DX12::IsFencePending(const SR_Fence& aFence)
{
	return mFence->IsPending(aFence.mValue);
}

bool SR_CommandQueue_DX12::WaitForFence(const SR_Fence& aFence, bool aBlock /*= true*/)
{
	return mFence->Wait(aFence.mValue, aBlock);
}

void SR_CommandQueue_DX12::BeginEvent(const char* /*aName*/)
{

}

void SR_CommandQueue_DX12::EndEvent()
{

}

ID3D12CommandQueue* SR_CommandQueue_DX12::GetD3D12CommandQueue() const
{
	return mD3D12CommandQueue.Get();
}

#endif
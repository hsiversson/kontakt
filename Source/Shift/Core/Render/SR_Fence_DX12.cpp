//ProjectFilter(DX12/Resources)
#include "Render_Precompiled.h"

#if SR_ENABLE_DX12
#include "SR_Fence_DX12.h"
#include "SR_RenderDevice_DX12.h"

SR_FenceResource_DX12::SR_FenceResource_DX12()
	: mFenceValue(0)
	, mLastKnownCompletedValue(0)
	, mCommandQueue(nullptr)
{

}

SR_FenceResource_DX12::~SR_FenceResource_DX12()
{

}

bool SR_FenceResource_DX12::IsPending(uint64 aValue)
{
	uint64 completedValue = mD3D12Fence->GetCompletedValue();
	if (completedValue > mLastKnownCompletedValue)
	{
		if (completedValue == UINT64_MAX) // Device Was Removed
		{
			SR_VerifyHRESULT(DXGI_ERROR_DEVICE_REMOVED);
			return true;
		}

		SC_Atomic::CompareExchange(mLastKnownCompletedValue, completedValue, mLastKnownCompletedValue);
	}

	return aValue > completedValue;
}

bool SR_FenceResource_DX12::Wait(uint64 aValue, bool aBlock)
{
	if (IsPending(aValue))
	{
		if (!aBlock)
			return false;

		HANDLE eventHandle = CreateEvent(nullptr, false, false, nullptr);
		if (!eventHandle)
		{
			SC_ASSERT(false, "Could not create event");
			return false;
		}

		HRESULT hr = mD3D12Fence->SetEventOnCompletion(aValue, eventHandle);
		if (SR_VerifyHRESULT(hr))
			WaitForSingleObject(eventHandle, INFINITE);

		CloseHandle(eventHandle);
	}
	return true;
}

uint64 SR_FenceResource_DX12::GetNextValue()
{
	return SC_Atomic::Increment_GetNew(mFenceValue);
}

uint64 SR_FenceResource_DX12::GetLatestValue()
{
	return (mFenceValue > 0) ? (mFenceValue - 1): mFenceValue;
}

ID3D12Fence* SR_FenceResource_DX12::GetD3D12Fence() const
{
	return mD3D12Fence.Get();
}

bool SR_FenceResource_DX12::Init()
{
	HRESULT hr = SR_RenderDevice_DX12::gInstance->GetD3D12Device()->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&mD3D12Fence));
	if (!SR_VerifyHRESULT(hr))
	{
		SC_ASSERT(false, "Could not create fence.");
		return false;
	}

	return true;
}

#endif
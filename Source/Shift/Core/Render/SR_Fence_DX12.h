//ProjectFilter(DX12/Resources)
#pragma once

#if SR_ENABLE_DX12
#include "SR_Fence.h"

struct ID3D12Fence;
class SR_CommandQueue_DX12;

class SR_FenceResource_DX12 final : public SR_FenceResource
{
	friend class SR_CommandQueue_DX12;
	friend class SR_RenderDevice_DX12;

public:
	SR_FenceResource_DX12();
	virtual ~SR_FenceResource_DX12();

	bool IsPending(uint64 aValue) override;
	bool Wait(uint64 aValue, bool aBlock = true) override;
	uint64 GetNextValue() override;
	uint64 GetLatestValue() override;

	ID3D12Fence* GetD3D12Fence() const;

private:
	bool Init();

	SR_ComPtr<ID3D12Fence> mD3D12Fence;

	volatile uint64 mFenceValue;
	volatile uint64 mLastKnownCompletedValue;

	SR_CommandQueue_DX12* mCommandQueue;
};

#endif
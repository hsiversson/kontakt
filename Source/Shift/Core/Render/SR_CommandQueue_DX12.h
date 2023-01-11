//ProjectFilter(DX12/CommandList)
#pragma once
#if SR_ENABLE_DX12

#include "SR_CommandQueue.h"
#include "SR_CommandList_DX12.h"

class SR_FenceResource_DX12;
class SR_CommandQueue_DX12 final : public SR_CommandQueue
{
public:
	SR_CommandQueue_DX12();
	~SR_CommandQueue_DX12();

	bool Init(const SR_CommandListType& aType, const char* aDebugName = nullptr);

	void SubmitCommandLists(SR_CommandList** aCmdLists, uint32 aNumCmdLists, const char* aEventName = nullptr) override;

	SR_Fence GetNextFence() override;

	void SignalFence(const SR_Fence& aFence) override; 
	void SignalFence(uint64 aValue, SR_FenceResource* aResource) override;
	void InsertWait(const SR_Fence& aFence) override;

	bool IsFencePending(const SR_Fence& aFence) override;
	bool WaitForFence(const SR_Fence& aFence, bool aBlock = true) override;

	void BeginEvent(const char* aName) override;
	void EndEvent() override;

	ID3D12CommandQueue* GetD3D12CommandQueue() const;

private:
	SR_ComPtr<ID3D12CommandQueue> mD3D12CommandQueue;
	SC_Ref<SR_FenceResource_DX12> mFence;
};

#endif
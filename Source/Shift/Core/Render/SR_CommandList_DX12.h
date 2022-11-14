#pragma once

#if SR_ENABLE_DX12
#include "SR_CommandList.h"

class SR_CommandList_DX12 final : public SR_CommandList
{
public:

	ID3D12CommandList* GetD3D12CommandList() const;

private:
	SR_ComPtr<ID3D12CommandList> mD3D12CommandList;
};

#endif
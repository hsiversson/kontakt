#include "Render_Precompiled.h"
#include "SR_CommandList_DX12.h"

ID3D12CommandList* SR_CommandList_DX12::GetD3D12CommandList() const
{
    return mD3D12CommandList.Get();
}

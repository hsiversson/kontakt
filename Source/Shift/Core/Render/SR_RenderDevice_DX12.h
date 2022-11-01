//ProjectFilter(DX12)
#pragma once
#include "SR_RenderDevice.h"

#if ENABLE_DX12

struct ID3D12Device;
struct ID3D12Device5;
struct ID3D12Device6;

class SR_RenderDevice_DX12 final : public SR_RenderDevice
{
public:
    SR_RenderDevice_DX12();
    ~SR_RenderDevice_DX12();

private:
    SR_ComPtr<ID3D12Device> mD3D12Device;
	SR_ComPtr<ID3D12Device5> mD3D12Device5;
	SR_ComPtr<ID3D12Device6> mD3D12Device6;
};

#endif
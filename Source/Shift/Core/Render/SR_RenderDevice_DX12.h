//ProjectFilter(DX12)
#pragma once
#include "SR_RenderDevice.h"

#if SR_ENABLE_DX12

struct ID3D12Device;
struct ID3D12Device5;
struct ID3D12Device6;

struct IDXGIFactory1;
struct IDXGIAdapter;
struct IDXGIAdapter3;

struct ID3D12InfoQueue;

class SR_RenderDevice_DX12 final : public SR_RenderDevice
{
public:
    SR_RenderDevice_DX12();
    ~SR_RenderDevice_DX12();

    bool Init() override;

	ID3D12Device* GetD3D12Device() const;
	ID3D12Device5* GetD3D12Device5() const;
	ID3D12Device6* GetD3D12Device6() const;

	static SR_RenderDevice_DX12* gInstance;

private:
    SR_ComPtr<ID3D12Device> mD3D12Device;
	SR_ComPtr<ID3D12Device5> mD3D12Device5;
	SR_ComPtr<ID3D12Device6> mD3D12Device6;
	SR_ComPtr<IDXGIFactory1> mDXGIFactory1;
	SR_ComPtr<IDXGIAdapter> mDXGIAdapter;
	SR_ComPtr<IDXGIAdapter3> mDXGIAdapter3;

	SR_ComPtr<ID3D12InfoQueue> mD3D12InfoQueue;

    bool mEnableGpuValidation;

#if SR_ENABLE_DRED
    bool mEnableDRED;
#endif
};

#endif
//ProjectFilter(DX12/Resources)
#pragma once

#if SR_ENABLE_DX12
#include "SR_Buffer.h"

class SR_Buffer_DX12 final : public SR_Buffer 
{
public:
	SR_Buffer_DX12(const SR_BufferProperties& aProperties, const SC_Ref<SR_BufferResource>& aResource);
	~SR_Buffer_DX12();

	bool Init();

	D3D12_CPU_DESCRIPTOR_HANDLE GetCPUHandleSRV() const;
	D3D12_GPU_DESCRIPTOR_HANDLE GetGPUHandleSRV() const;

	D3D12_CPU_DESCRIPTOR_HANDLE GetCPUHandleUAV() const;
	D3D12_GPU_DESCRIPTOR_HANDLE GetGPUHandleUAV() const;
private:
	bool InitSRV();
	bool InitUAV();

};

#endif


#pragma once
#include "SR_Texture.h"

#if SR_ENABLE_DX12
class SR_TextureResource_DX12;
class SR_Texture_DX12 : public SR_Texture
{
public:
	SR_Texture_DX12(const SR_TextureProperties& aProperties, const SC_Ref<SR_TextureResource>& aTextureResource);
	~SR_Texture_DX12();

	bool Init();

	D3D12_CPU_DESCRIPTOR_HANDLE GetCPUHandle(const SR_TextureBindType& aDescriptorType) const;
	D3D12_GPU_DESCRIPTOR_HANDLE GetGPUHandle(const SR_TextureBindType& aDescriptorType) const;

private:
	bool InitSRV();
	bool InitUAV();
	bool InitRTV();
	bool InitDSV();

	SR_TextureResource_DX12* mDX12Resource;
};
#endif
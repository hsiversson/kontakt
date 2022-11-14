//ProjectFilter(DX12/Resources)
#pragma once
#include "SR_TextureResource.h"

#if SR_ENABLE_DX12

struct ID3D12Resource;
class SR_TextureResource_DX12 : public SR_TextureResource
{
public:
	SR_TextureResource_DX12(const SR_TextureResourceProperties& aProperties);
	SR_TextureResource_DX12(const SR_TextureResourceProperties& aProperties, ID3D12Resource* aResource);
	~SR_TextureResource_DX12();

	bool Init(const SR_PixelData* aInitialData, uint32 aDataCount);
};

#endif

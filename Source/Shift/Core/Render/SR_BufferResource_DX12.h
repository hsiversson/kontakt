//ProjectFilter(DX12/Resources)
#pragma once

#if SR_ENABLE_DX12
#include "SR_BufferResource.h"

class SR_BufferResource_DX12 final : public SR_BufferResource
{
public:
	SR_BufferResource_DX12(const SR_BufferResourceProperties& aProperties);
	~SR_BufferResource_DX12();

	bool Init(const void* aInitialData);
};

#endif
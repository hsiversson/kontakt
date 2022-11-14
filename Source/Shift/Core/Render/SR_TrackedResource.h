//ProjectFilter(Interface)
#pragma once
#include "SR_Resource.h"

#if SR_ENABLE_DX12
struct ID3D12Resource;
#endif

class SR_TrackedResource : public SR_Resource
{
public:
	SR_TrackedResource();
	virtual ~SR_TrackedResource();

#if SR_ENABLE_DX12
	ID3D12Resource* mD3D12Resource;
#endif
};


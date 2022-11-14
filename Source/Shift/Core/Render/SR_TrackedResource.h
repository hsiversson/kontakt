//ProjectFilter(Interface)
#pragma once
#include "SR_Resource.h"

struct ID3D12Resource;

class SR_TrackedResource : public SR_Resource
{
public:
	SR_TrackedResource();
	virtual ~SR_TrackedResource();

#if SR_ENABLE_DX12
	SR_ComPtr<ID3D12Resource> mD3D12Resource;
#endif
};


//ProjectFilter(Interface)
#pragma once
#include "SR_Resource.h"

#if SR_ENABLE_DX12
struct ID3D12Resource;
struct SR_ResourceTracking_DX12
{
	uint32 mD3D12CurrentState;
	uint32 mD3D12ReadState;
};
#endif

class SR_TrackedResource : public SR_Resource
{
public:
	SR_TrackedResource();
	virtual ~SR_TrackedResource();

#if SR_ENABLE_DX12
	ID3D12Resource* mD3D12Resource;
#endif

	union
	{
#if SR_ENABLE_DX12
		SR_ResourceTracking_DX12 mResourceTrackingDX12;
#endif
	};

	uint32 mCurrentState;
	bool mIsBuffer;
};


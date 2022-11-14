//ProjectFilter(Interface)
#include "Render_Precompiled.h"
#include "SR_TrackedResource.h"

SR_TrackedResource::SR_TrackedResource()
{
#if SR_ENABLE_DX12
	mD3D12Resource = nullptr;
#endif
}

SR_TrackedResource::~SR_TrackedResource()
{
#if SR_ENABLE_DX12
	if (mD3D12Resource)
		mD3D12Resource->Release();
#endif
}

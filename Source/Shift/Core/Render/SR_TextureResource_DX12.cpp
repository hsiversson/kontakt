//ProjectFilter(DX12/Resources)
#include "Render_Precompiled.h"

#if SR_ENABLE_DX12
#include "SR_TextureResource_DX12.h"
#include "SR_RenderDevice_DX12.h"

SR_TextureResource_DX12::SR_TextureResource_DX12(const SR_TextureResourceProperties& aProperties)
	: SR_TextureResource(aProperties)
{

}

SR_TextureResource_DX12::SR_TextureResource_DX12(const SR_TextureResourceProperties& aProperties, ID3D12Resource* aResource)
	: SR_TextureResource(aProperties)
{
	mD3D12Resource = aResource;
}

SR_TextureResource_DX12::~SR_TextureResource_DX12()
{

}

bool SR_TextureResource_DX12::Init(const SR_PixelData* /*aInitialData*/, uint32 /*aDataCount*/)
{
	D3D12_RESOURCE_DESC resourceDesc = SR_GetResourceDesc_DX12(mProperties);

	bool useOptimizedClearValue = (mProperties.mAllowDepthStencil || mProperties.mAllowRenderTarget) && (resourceDesc.Dimension != D3D12_RESOURCE_DIMENSION_BUFFER);

	D3D12_CLEAR_VALUE optimizedClearValue;
	optimizedClearValue.Color[0] = 0.0f;
	optimizedClearValue.Color[1] = 0.0f;
	optimizedClearValue.Color[2] = 0.0f;
	optimizedClearValue.Color[3] = 0.0f;
	optimizedClearValue.Format = resourceDesc.Format;

	D3D12_RESOURCE_STATES initialState = D3D12_RESOURCE_STATE_COMMON;
	HRESULT hr = S_OK;

	D3D12_HEAP_PROPERTIES heapProps = {};
	heapProps.Type = D3D12_HEAP_TYPE_DEFAULT;
	heapProps.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
	heapProps.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
	heapProps.CreationNodeMask = 1;
	heapProps.VisibleNodeMask = 1;

	hr = SR_RenderDevice_DX12::gInstance->GetD3D12Device()->CreateCommittedResource(&heapProps, D3D12_HEAP_FLAG_NONE, &resourceDesc, initialState, useOptimizedClearValue ? &optimizedClearValue : nullptr, IID_PPV_ARGS(&mD3D12Resource));
	if (!SR_VerifyHRESULT(hr))
	{
		SC_ASSERT(false, "Could not create texture.");
		return false;
	}

	if (!mProperties.mDebugName.empty())
	{
		std::wstring debugName;
		SC_UTF::ToUTF16(debugName, mProperties.mDebugName.c_str(), (uint32)mProperties.mDebugName.length());
		mD3D12Resource->SetName(debugName.c_str());
	}

	//if (aInitialData)
	//	UpdatePixels(aInitialData, aDataCount);

	return true;
}

#endif
//ProjectFilter(DX12)
#include "Render_Precompiled.h"

#if SR_ENABLE_DX12
#include "SR_RenderDevice_DX12.h"
#include "SR_TextureResource_DX12.h"
#include "SR_Texture_DX12.h"
#include "SR_SwapChain_DX12.h"

extern "C" { __declspec(dllexport) extern const UINT D3D12SDKVersion = 606; }
extern "C" { __declspec(dllexport) extern const char* D3D12SDKPath = "./"; }

SR_RenderDevice_DX12* SR_RenderDevice_DX12::gInstance = nullptr;

SR_RenderDevice_DX12::SR_RenderDevice_DX12()
{
	mRenderApi = SR_API::D3D12;

	gInstance = this;
}

SR_RenderDevice_DX12::~SR_RenderDevice_DX12()
{
	gInstance = nullptr;
}

bool SR_RenderDevice_DX12::Init()
{
	if (mEnableDebugMode)
	{
		SC_LOG("D3D12 Debug Layer: Enabled");
		SR_ComPtr<ID3D12Debug> debugger;
		D3D12GetDebugInterface(IID_PPV_ARGS(&debugger));
		debugger->EnableDebugLayer();

		SR_ComPtr<ID3D12Debug6> debugger6;
		debugger->QueryInterface(IID_PPV_ARGS(&debugger6));
		if (debugger6)
			debugger6->SetEnableAutoName(true);
	}

	if (mEnableGpuValidation)
	{
		SC_LOG("D3D12 GPU-based Validation: Enabled");
		SR_ComPtr<ID3D12Debug1> debugger;
		D3D12GetDebugInterface(IID_PPV_ARGS(&debugger));
		debugger->SetEnableGPUBasedValidation(true);
		debugger->SetEnableSynchronizedCommandQueueValidation(true);

	}

#if SR_ENABLE_DRED
	if (mEnableDRED)
	{
		SC_LOG("D3D12 DRED: Enabled");
		SR_ComPtr<ID3D12DeviceRemovedExtendedDataSettings1> dredSettings;
		D3D12GetDebugInterface(IID_PPV_ARGS(&dredSettings));
		dredSettings->SetAutoBreadcrumbsEnablement(D3D12_DRED_ENABLEMENT_FORCED_ON);
		dredSettings->SetPageFaultEnablement(D3D12_DRED_ENABLEMENT_FORCED_ON);
	}
#endif

	HRESULT hr = mDXGIAdapter.As(&mDXGIAdapter3);

	SC_LOG("Creating D3D12Device.");
	hr = D3D12CreateDevice(mDXGIAdapter.Get(), D3D_FEATURE_LEVEL_12_0, IID_PPV_ARGS(&mD3D12Device));

	hr = mD3D12Device.As(&mD3D12Device5);
	hr = mD3D12Device.As(&mD3D12Device6);
	//GatherSupportCaps();

	if (mEnableDebugMode)
	{
		if (SUCCEEDED(mD3D12Device->QueryInterface(IID_PPV_ARGS(&mD3D12InfoQueue))))
		{
			D3D12_MESSAGE_SEVERITY severities[] =
			{
				D3D12_MESSAGE_SEVERITY_INFO
			};
			D3D12_MESSAGE_ID denyIds[] =
			{
				D3D12_MESSAGE_ID_CLEARRENDERTARGETVIEW_MISMATCHINGCLEARVALUE,
				D3D12_MESSAGE_ID_CLEARDEPTHSTENCILVIEW_MISMATCHINGCLEARVALUE
			};

			D3D12_INFO_QUEUE_FILTER newFilter = {};
			newFilter.DenyList.NumSeverities = _countof(severities);
			newFilter.DenyList.pSeverityList = severities;
			newFilter.DenyList.NumIDs = _countof(denyIds);
			newFilter.DenyList.pIDList = denyIds;
			mD3D12InfoQueue->PushStorageFilter(&newFilter);
			if (mEnableBreakOnError)
			{
				mD3D12InfoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_CORRUPTION, true);
				mD3D12InfoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_ERROR, true);
			}
		}
	}

	return false;
}

SC_Ref<SR_TextureResource> SR_RenderDevice_DX12::CreateTextureResource(const SR_TextureResourceProperties& aTextureResourceProperties, const SR_PixelData* aInitialData, uint32 aDataCount)
{
	SC_Ref<SR_TextureResource_DX12> newTextureResource = new SR_TextureResource_DX12(aTextureResourceProperties);

	if (!newTextureResource->Init(aInitialData, aDataCount))
		return nullptr;

	return newTextureResource;
}

SC_Ref<SR_Texture> SR_RenderDevice_DX12::CreateTexture(const SR_TextureProperties& aTextureProperties, const SC_Ref<SR_TextureResource>& aResource)
{
	SC_Ref<SR_Texture_DX12> newTexture = new SR_Texture_DX12(aTextureProperties, aResource);

	if (!newTexture->Init())
		return nullptr;

	return newTexture;
}

SR_CommandQueue* SR_RenderDevice_DX12::GetCommandQueue(const SR_CommandListType& /*aType*/) const
{
	return nullptr;
}

SR_DescriptorHeap* SR_RenderDevice_DX12::GetDescriptorHeap(const SR_DescriptorType& aDescriptorType) const
{
	switch (aDescriptorType)
	{
	case SR_DescriptorType::CBV:
	case SR_DescriptorType::SRV:
	case SR_DescriptorType::UAV:
		return mDefaultDescriptorHeap;

	case SR_DescriptorType::RTV:
		return mRTVDescriptorHeap;

	case SR_DescriptorType::DSV:
		return mDSVDescriptorHeap;

	case SR_DescriptorType::Sampler:
		return mSamplerDescriptorHeap;

	default:
		return nullptr;
	}
}

SC_Ref<SR_SwapChain> SR_RenderDevice_DX12::CreateSwapChain(const SR_SwapChainProperties& aProperties, void* aNativeWindowHandle)
{
	SC_Ref<SR_SwapChain_DX12> newSwapChain = new SR_SwapChain_DX12();

	if (!newSwapChain->Init(aProperties, aNativeWindowHandle))
		return nullptr;

	return newSwapChain;
}

ID3D12Device* SR_RenderDevice_DX12::GetD3D12Device() const
{
	return mD3D12Device.Get();
}

ID3D12Device5* SR_RenderDevice_DX12::GetD3D12Device5() const
{
	return mD3D12Device5.Get();
}

ID3D12Device6* SR_RenderDevice_DX12::GetD3D12Device6() const
{
	return mD3D12Device6.Get();
}

#endif
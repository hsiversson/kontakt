//ProjectFilter(DX12)
#include "Render_Precompiled.h"

#if SR_ENABLE_DX12
#include "SR_SwapChain_DX12.h"
#include "SR_RenderDevice_DX12.h"
#include "SR_CommandQueue_DX12.h"
#include "SR_TextureResource_DX12.h"

SR_SwapChain_DX12::SR_SwapChain_DX12()
	: mSwapChainFlags(0)
	, mWindowHandle(nullptr)
{

}

SR_SwapChain_DX12::~SR_SwapChain_DX12()
{

}

bool SR_SwapChain_DX12::Init(const SR_SwapChainProperties& aProperties, void* aWindowHandle)
{
	mDXGIFactory = SR_RenderDevice_DX12::gInstance->GetDXGIFactory1();

	HRESULT hr = mDXGIFactory.As(&mDXGIFactory4);
	if (!SR_VerifyHRESULT(hr))
		return false;

	hr = mDXGIFactory.As(&mDXGIFactory5);
	if (!SR_VerifyHRESULT(hr))
		return false;

	mProperties = aProperties;
	mWindowHandle = aWindowHandle;

	if (!CreateSwapChain())
		return false;

	if (!CreateResources())
		return false;

	return true;
}

bool SR_SwapChain_DX12::UpdateProperties(const SR_SwapChainProperties& aProperties)
{
	return SR_SwapChain::UpdateProperties(aProperties);
}

void SR_SwapChain_DX12::Present()
{
	bool vsync = false;

	uint32 flags = 0;
	if (!vsync && (mSwapChainFlags & DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING))
		flags |= DXGI_PRESENT_ALLOW_TEARING;

	uint32 interval = 0;
	/*HRESULT hr =*/ mDXGISwapChain->Present(interval, flags);

	mCurrentIndex = mDXGISwapChain3->GetCurrentBackBufferIndex();
}

bool SR_SwapChain_DX12::CreateSwapChain()
{
	BOOL allowTearing = FALSE;
	HRESULT hr = mDXGIFactory5->CheckFeatureSupport(DXGI_FEATURE_PRESENT_ALLOW_TEARING, &allowTearing, sizeof(allowTearing));
	if (!SR_VerifyHRESULT(hr))
		return false;

	mNumBackbuffers = 2; // fullscreen & triplebuffer == 3

	DXGI_SWAP_CHAIN_DESC1 desc = {};
	desc.Width = mProperties.mSize.x;
	desc.Height = mProperties.mSize.y;
	desc.Format = SR_ConvertFormat_DX12(mProperties.mFormat);
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.BufferCount = (uint32)mNumBackbuffers;
	desc.Stereo = false;
	desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	if (!allowTearing)
		desc.Flags |= DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING;

	mSwapChainFlags = desc.Flags; // Store flags for internal swapchain updates

	DXGI_SWAP_CHAIN_FULLSCREEN_DESC fullscreenDesc = {};
	fullscreenDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	fullscreenDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_PROGRESSIVE;
	fullscreenDesc.Windowed = true;
	fullscreenDesc.RefreshRate.Numerator = 0;
	fullscreenDesc.RefreshRate.Denominator = 1;

	SR_CommandQueue_DX12* cmdQueue = static_cast<SR_CommandQueue_DX12*>(SR_RenderDevice_DX12::gInstance->GetCommandQueue(SR_CommandListType::Graphics));
	hr = mDXGIFactory4->CreateSwapChainForHwnd(cmdQueue->GetD3D12CommandQueue(), static_cast<HWND>(mWindowHandle), &desc, &fullscreenDesc, nullptr, &mDXGISwapChain);
	if (!SR_VerifyHRESULT(hr))
		return false;

	hr = mDXGIFactory->MakeWindowAssociation(HWND(mWindowHandle), DXGI_MWA_NO_WINDOW_CHANGES);
	if (!SR_VerifyHRESULT(hr))
		return false;

	hr = mDXGISwapChain.As(&mDXGISwapChain3);
	if (!SR_VerifyHRESULT(hr))
		return false;

	return true;
}

bool SR_SwapChain_DX12::CreateResources()
{
	DestroyResources();

	if (!mDXGISwapChain)
		return false;

	DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
	mDXGISwapChain->GetDesc(&swapChainDesc);

	for (uint32 i = 0; i < swapChainDesc.BufferCount; ++i)
	{
		ID3D12Resource* res = nullptr;
		HRESULT hr = mDXGISwapChain->GetBuffer(i, IID_PPV_ARGS(&res));
		if (!SR_VerifyHRESULT(hr))
		{
			SC_ASSERT(false);
			return false;
		}

		std::wstring name(L"Framebuffer Texture " + std::to_wstring(i));
		res->SetName(name.c_str());

		D3D12_RESOURCE_DESC desc = res->GetDesc();

		SR_TextureResourceProperties framebufferProperties;
		framebufferProperties.mSize.x = (int)desc.Width;
		framebufferProperties.mSize.y = (int)desc.Height;
		framebufferProperties.mNumMips = desc.MipLevels;
		framebufferProperties.mFormat = SR_ConvertFormat_DX12(desc.Format);
		framebufferProperties.mAllowRenderTarget = true;
		framebufferProperties.mAllowWrites = true;
		framebufferProperties.mType = SR_ResourceType::Texture2D;
		mBackbufferResources[i].mResource = new SR_TextureResource_DX12(framebufferProperties, res);
		//mBackbufferResources[i].mResource->mLatestResourceState = SR_ResourceState_Present;

		SR_TextureProperties texProperties(framebufferProperties.mFormat, SR_TextureBindFlag_Texture | SR_TextureBindFlag_RWTexture | SR_TextureBindFlag_RenderTarget);
		mBackbufferResources[i].mTexture = SR_RenderDevice_DX12::gInstance->CreateTexture(texProperties, mBackbufferResources[i].mResource);
	}

	mCurrentResource = &mBackbufferResources[mCurrentIndex];
	return true;
}

bool SR_SwapChain_DX12::DestroyResources()
{
	if (!SR_RenderDevice_DX12::gInstance)
		return false;

	for (uint32 i = 0; i < 3; ++i)
	{
		mBackbufferResources[i].mTexture = nullptr;
		mBackbufferResources[i].mResource = nullptr;
	}

	mCurrentResource = nullptr;

	return true;
}

#endif
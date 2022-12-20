//ProjectFilter(DX12)
#pragma once

#if SR_ENABLE_DX12
#include "SR_SwapChain.h"

struct IDXGIFactory1;
struct IDXGIFactory4;
struct IDXGIFactory5;
struct IDXGISwapChain1;
struct IDXGISwapChain3;

class SR_SwapChain_DX12 final : public SR_SwapChain
{
public:
	SR_SwapChain_DX12();
	~SR_SwapChain_DX12();

	bool Init(const SR_SwapChainProperties& aProperties, void* aWindowHandle);
	bool UpdateProperties(const SR_SwapChainProperties& aProperties) override;

	void Present() override;

private:
	bool CreateSwapChain();
	bool CreateResources();
	bool DestroyResources();

private:
	SR_ComPtr<IDXGIFactory1> mDXGIFactory;
	SR_ComPtr<IDXGIFactory4> mDXGIFactory4;
	SR_ComPtr<IDXGIFactory5> mDXGIFactory5;
	SR_ComPtr<IDXGISwapChain1> mDXGISwapChain;
	SR_ComPtr<IDXGISwapChain3> mDXGISwapChain3;

	uint32 mSwapChainFlags;
	void* mWindowHandle;
};

#endif
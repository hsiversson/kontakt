//ProjectFilter(Windows)
#include "AppFramework_Precompiled.h"

#if IS_WINDOWS_PLATFORM
#include "SAF_Application_Win64.h"
#include "SC_CommandLine.h"

#include "SR_RenderDevice.h"

SAF_Application_Win64::SAF_Application_Win64()
{

}

SAF_Application_Win64::~SAF_Application_Win64()
{

}

bool SAF_Application_Win64::Init()
{
	if (!SC_CommandLine::Init(__argv, __argc))
		return false;

	SR_API renderApi = SR_API::D3D12;

#if SR_ENABLE_DX12
	if (SC_CommandLine::HasCommand("dx12"))
		renderApi = SR_API::D3D12;
#endif
#if SR_ENABLE_VULKAN
	if (SC_CommandLine::HasCommand("vulkan"))
		renderApi = SR_API::Vulkan;
#endif

	if (!SR_RenderDevice::Create(renderApi))
	{
		SC_ASSERT(false, "Failed to init RenderDevice.");
		return false;
	}

	if (!mWindow.Init())
		return false;

	SR_SwapChainProperties swapChainProps = {};
	swapChainProps.mFormat = SR_Format::RGBA8_UNORM;
	swapChainProps.mFullscreen = false;
	swapChainProps.mTripleBuffer = false;
	swapChainProps.mSize = SC_Vector2i(1920, 1080);

	mWindow.mSwapChain = SR_RenderDevice::gInstance->CreateSwapChain(swapChainProps, mWindow.GetHandle());
	if (!mWindow.mSwapChain)
		return false;

	//SR_RenderDevice::gInstance->SetSwapChain(window->mSwapChain);

	return SAF_Application::Init();
}

bool SAF_Application_Win64::Update(SAF_ReturnCode& aOutReturnCode)
{
	{
		MSG msg = {};
		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				return false;

			DispatchMessage(&msg);
		}
	}

	return SAF_Application::Update(aOutReturnCode);
}

#endif

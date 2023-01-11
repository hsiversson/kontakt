//ProjectFilter(Interface)
#include "Render_Precompiled.h"
#include "SR_RenderDevice.h"

#if SR_ENABLE_DX12
#include "SR_RenderDevice_DX12.h"
#endif
#if SR_ENABLE_VULKAN
#include "SR_RenderDevice_Vk.h"
#endif

// TEMP
#include "SR_RenderContext.h"
#include "SR_CommandList_DX12.h"
// TEMP END

SR_RenderDevice* SR_RenderDevice::gInstance = nullptr;

struct triplebufferer
{
	void advance()
	{
	}

	volatile uint32 currentIndex;
	volatile uint32 numFramesInFlight;
};

SR_RenderDevice::SR_RenderDevice()
	: mEnableDebugMode(false)
	, mEnableBreakOnError(false)
{
	if (SC_CommandLine::HasArgument("debugrender"))
		mEnableDebugMode = true;
}

SR_RenderDevice::~SR_RenderDevice()
{
	for (uint32 i = 0; i < static_cast<uint32>(SR_CommandListType::COUNT); ++i)
	{
		mContextThreads[i]->Stop(true);
		delete mContextThreads[i];
		mContextThreads[i] = nullptr;
	}
}

void SR_RenderDevice::BeginFrame()
{
	// Post Frame Task
	// Begin RenderFrame

	//auto beginFrameTask = []()
	//{
	//};
	//PostRenderTask(SR_CommandListType::Graphics, beginFrameTask);

}

void SR_RenderDevice::EndFrame()
{
	// Post Frame Task
	// End RenderFrame

	//auto endFrameTask = []()
	//{
	//};
	//PostRenderTask(SR_CommandListType::Graphics, endFrameTask);
}

void SR_RenderDevice::Present()
{
	auto presentTask = [&]()
	{
		mCurrentSwapChain->Present();
	};
	SC_Ref<SC_Event> ev = PostRenderTask(SR_CommandListType::Graphics, presentTask);
	ev->Wait();
}

SC_Ref<SC_Event> SR_RenderDevice::PostRenderTask(const SR_CommandListType& aType, std::function<void()> aTask)
{
	return mContextThreads[static_cast<uint32>(aType)]->PostTask(aTask);
}

SC_Ref<SC_Event> SR_RenderDevice::PostGraphicsTask(std::function<void()> aTask)
{
	return PostRenderTask(SR_CommandListType::Graphics, aTask);
}

SC_Ref<SC_Event> SR_RenderDevice::PostComputeTask(std::function<void()> aTask)
{
	return PostRenderTask(SR_CommandListType::Compute, aTask);
}

SC_Ref<SC_Event> SR_RenderDevice::PostCopyTask(std::function<void()> aTask)
{
	return PostRenderTask(SR_CommandListType::Copy, aTask);
}

SC_Ref<SR_CommandList> SR_RenderDevice::CreateCommandList(const SR_CommandListType& /*aType*/)
{
	SC_ASSERT(false, "Not Implemented Yet!");
	return nullptr;
}

SC_Ref<SR_TextureResource> SR_RenderDevice::CreateTextureResource(const SR_TextureResourceProperties& /*aTextureResourceProperties*/, const SR_PixelData* /*aInitialData*/, uint32 /*aDataCount*/)
{
	SC_ASSERT(false, "Not Implemented Yet!");
	return nullptr;
}

SC_Ref<SR_Texture> SR_RenderDevice::CreateTexture(const SR_TextureProperties& /*aTextureProperties*/, const SC_Ref<SR_TextureResource>& /*aResource*/)
{
	SC_ASSERT(false, "Not Implemented Yet!");
	return nullptr;
}

SC_Ref<SR_BufferResource> SR_RenderDevice::CreateBufferResource(const SR_BufferResourceProperties& /*aBufferResourceProperties*/, const void* /*aInitialData*/)
{
	SC_ASSERT(false, "Not Implemented Yet!");
	return nullptr;
}

SC_Ref<SR_Buffer> SR_RenderDevice::CreateBuffer(const SR_BufferProperties& /*aBufferProperties*/, const SC_Ref<SR_BufferResource>& /*aResource*/)
{
	SC_ASSERT(false, "Not Implemented Yet!");
	return nullptr;
}

SC_Ref<SR_Shader> SR_RenderDevice::CreateShader(const SR_CreateShaderProperties& /*aCreateShaderProperties*/)
{
	SC_ASSERT(false, "Not Implemented Yet!");
	return nullptr;
}

SC_Ref<SR_PipelineState> SR_RenderDevice::CreatePipelineState()
{
	SC_ASSERT(false, "Not Implemented Yet!");
	return nullptr;
}

SC_Ref<SR_FenceResource> SR_RenderDevice::CreateFenceResource()
{
	SC_ASSERT(false, "Not Implemented Yet!");
	return nullptr;
}

SR_CommandQueue* SR_RenderDevice::GetCommandQueue(const SR_CommandListType& aType) const
{
	return mCommandQueues[static_cast<uint32>(aType)];
}

SR_DescriptorHeap* SR_RenderDevice::GetDescriptorHeap(const SR_DescriptorHeapType& /*aDescriptorHeapType*/) const
{
	SC_ASSERT(false, "Not Implemented Yet!");
	return nullptr;
}

SC_Ref<SR_SwapChain> SR_RenderDevice::CreateSwapChain(const SR_SwapChainProperties& /*aProperties*/, void* /*aNativeWindowHandle*/)
{
	SC_ASSERT(false, "Not Implemented Yet!");
	return nullptr;
}

const SR_API& SR_RenderDevice::GetAPI() const
{
	return mRenderApi;
}

SR_RootSignature* SR_RenderDevice::GetRootSignature(const SR_RootSignatureType& aType) const
{
	return mRootSignatures[static_cast<uint32>(aType)];
}

SR_ShaderCompiler* SR_RenderDevice::GetShaderCompiler() const
{
	return mShaderCompiler;
}

SR_SwapChain* SR_RenderDevice::GetCurrentSwapChain() const
{
	return mCurrentSwapChain;
}

void SR_RenderDevice::SetCurrentSwapChain(SR_SwapChain* aSwapChain)
{
	mCurrentSwapChain = aSwapChain;
}

bool SR_RenderDevice::Create(const SR_API& aAPIType)
{
	if (gInstance)
	{
		SC_ASSERT(false, "RenderDevice can only be created once!");
		return false;
	}

	switch (aAPIType)
	{
#if SR_ENABLE_DX12
	case SR_API::D3D12:
		gInstance = new SR_RenderDevice_DX12();
		break;
#endif
#if SR_ENABLE_VULKAN
	case SR_API::Vulkan:
		gInstance = new SR_RenderDevice_Vk();
		break;
#endif
	case SR_API::Unknown:
	default:
		SC_ASSERT(false, "Invalid render API.");
		return false;
	}

	if (!gInstance->Init())
	{
		SC_ASSERT(false, "Couldn't initialize render api.");
		return false;
	}

	return true;
}

void SR_RenderDevice::Destroy()
{
	if (gInstance == nullptr)
		return;

	delete gInstance;
	gInstance = nullptr;
}

bool SR_RenderDevice::PostInit()
{
	mContextThreads[static_cast<uint32>(SR_CommandListType::Graphics)] = new SR_ContextThread(SR_CommandListType::Graphics);
	mContextThreads[static_cast<uint32>(SR_CommandListType::Graphics)]->Init();
	mContextThreads[static_cast<uint32>(SR_CommandListType::Graphics)]->SetName("Render Graphics");
	mContextThreads[static_cast<uint32>(SR_CommandListType::Graphics)]->Start();

	mContextThreads[static_cast<uint32>(SR_CommandListType::Compute)] = new SR_ContextThread(SR_CommandListType::Compute);
	mContextThreads[static_cast<uint32>(SR_CommandListType::Compute)]->Init();
	mContextThreads[static_cast<uint32>(SR_CommandListType::Compute)]->SetName("Render Compute");
	mContextThreads[static_cast<uint32>(SR_CommandListType::Compute)]->Start();

	mContextThreads[static_cast<uint32>(SR_CommandListType::Copy)] = new SR_ContextThread(SR_CommandListType::Copy);
	mContextThreads[static_cast<uint32>(SR_CommandListType::Copy)]->Init();
	mContextThreads[static_cast<uint32>(SR_CommandListType::Copy)]->SetName("Render Copy");
	mContextThreads[static_cast<uint32>(SR_CommandListType::Copy)]->Start();

	return true;
}

//ProjectFilter(Interface)
#include "Render_Precompiled.h"
#include "SR_RenderDevice.h"

#if SR_ENABLE_DX12
#include "SR_RenderDevice_DX12.h"
#endif
#if SR_ENABLE_VULKAN
#include "SR_RenderDevice_Vk.h"
#endif

SR_RenderDevice* SR_RenderDevice::gInstance = nullptr;

SR_RenderDevice::SR_RenderDevice()
	: mEnableDebugMode(false)
	, mEnableBreakOnError(false)
{
	if (SC_CommandLine::HasCommand("debugrender"))
		mEnableDebugMode = true;
}

SR_RenderDevice::~SR_RenderDevice()
{
}

void SR_RenderDevice::BeginFrame()
{
}

void SR_RenderDevice::EndFrame()
{
}

void SR_RenderDevice::Present()
{
	mCurrentSwapChain->Present();
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

SC_Ref<SR_BufferResource> SR_RenderDevice::CreateBufferResource()
{
	SC_ASSERT(false, "Not Implemented Yet!");
	return nullptr;
}

SC_Ref<SR_Buffer> SR_RenderDevice::CreateBufferView()
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

SR_CommandQueue* SR_RenderDevice::GetCommandQueue(const SR_CommandListType& /*aType*/) const
{
	SC_ASSERT(false, "Not Implemented Yet!");
	return nullptr;
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

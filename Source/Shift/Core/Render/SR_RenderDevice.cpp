//ProjectFilter(Interface)
#include "Render_Precompiled.h"
#include "SR_RenderDevice.h"

SR_RenderDevice* SR_RenderDevice::gInstance = nullptr;

SR_RenderDevice::SR_RenderDevice()
{
	gInstance = this;
}

SR_RenderDevice::~SR_RenderDevice()
{
	gInstance = nullptr;
}

SC_Ref<SR_TextureResource> SR_RenderDevice::CreateTextureResource()
{
	SC_ASSERT(false, "Not Implemented Yet!");
	return nullptr;
}

SC_Ref<SR_Texture> SR_RenderDevice::CreateTexture()
{
	SC_ASSERT(false, "Not Implemented Yet!");
	return nullptr;
}

SC_Ref<SR_BufferResource> SR_RenderDevice::CreateBufferResource()
{
	SC_ASSERT(false, "Not Implemented Yet!");
	return nullptr;
}

SC_Ref<SR_BufferView> SR_RenderDevice::CreateBufferView()
{
	SC_ASSERT(false, "Not Implemented Yet!");
	return nullptr;
}

SC_Ref<SR_Shader> SR_RenderDevice::CreateShader()
{
	SC_ASSERT(false, "Not Implemented Yet!");
	return nullptr;
}

SC_Ref<SR_PipelineState> SR_RenderDevice::CreatePipelineState()
{
	SC_ASSERT(false, "Not Implemented Yet!");
	return nullptr;
}

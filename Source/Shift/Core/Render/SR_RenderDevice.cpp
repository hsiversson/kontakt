//ProjectFilter(Interface)
#include "Render_Precompiled.h"
#include "SR_RenderDevice.h"

SR_RenderDevice::SR_RenderDevice()
{
}

SR_RenderDevice::~SR_RenderDevice()
{
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

//ProjectFilter(Interface)
#pragma once

#include "SR_Texture.h"
#include "SR_BufferView.h"

class SR_RenderDevice
{
public:
    SR_RenderDevice();
    virtual ~SR_RenderDevice();

    virtual bool Init();

    SC_Ref<SR_TextureResource> CreateBufferResource();
    SC_Ref<SR_Texture> CreateTexture();

    SC_Ref<SR_BufferResource> CreateBufferResource();
    SC_Ref<SR_BufferView> CreateBufferView();
private:
};
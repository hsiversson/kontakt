#pragma once

#include "SR_Texture.h"
#include "SR_BufferView.h"

class SR_RenderDevice
{
public:
    RenderDevice();
    virtual ~RenderDevice();

    virtual bool Init();

    Ref<SR_TextureResource> CreateBufferResource();
    Ref<SR_Texture> CreateTexture();

    Ref<SR_BufferResource> CreateBufferResource();
    Ref<SR_BufferView> CreateBufferView();
private:
};
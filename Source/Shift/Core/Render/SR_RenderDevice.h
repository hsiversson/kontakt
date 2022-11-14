//ProjectFilter(Interface)
#pragma once

#include "SR_Texture.h"
#include "SR_BufferView.h"
#include "SR_Shader.h"
#include "SR_PipelineState.h"

class SR_RenderDevice
{
public:
    SR_RenderDevice();
    virtual ~SR_RenderDevice();

    virtual bool Init() = 0;

    SC_Ref<SR_TextureResource> CreateTextureResource();
    SC_Ref<SR_Texture> CreateTexture();

    SC_Ref<SR_BufferResource> CreateBufferResource();
    SC_Ref<SR_BufferView> CreateBufferView();

    SC_Ref<SR_Shader> CreateShader();
    SC_Ref<SR_PipelineState> CreatePipelineState();

    static SR_RenderDevice* gInstance;

protected:
    bool mEnableDebugMode;
    bool mEnableBreakOnError;
};

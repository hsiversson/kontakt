//ProjectFilter(Interface)
#pragma once

#include "SR_Texture.h"
#include "SR_BufferView.h"
#include "SR_Shader.h"
#include "SR_PipelineState.h"

#include "SR_CommandQueue.h"
#include "SR_DescriptorHeap.h"

class SR_RenderDevice
{
public:
    SR_RenderDevice();
    virtual ~SR_RenderDevice();

    virtual bool Init() = 0;

	virtual SC_Ref<SR_TextureResource> CreateTextureResource(const SR_TextureResourceProperties& aTextureResourceProperties, const SR_PixelData* aInitialData = nullptr, uint32 aDataCount = 0);
	virtual SC_Ref<SR_Texture> CreateTexture(const SR_TextureProperties& aTextureProperties, const SC_Ref<SR_TextureResource>& aResource);

	virtual SC_Ref<SR_BufferResource> CreateBufferResource();
	virtual SC_Ref<SR_BufferView> CreateBufferView();

    virtual SC_Ref<SR_Shader> CreateShader();
    virtual SC_Ref<SR_PipelineState> CreatePipelineState();

	virtual SR_CommandQueue* GetCommandQueue(const SR_CommandListType& aType) const;
	virtual SR_DescriptorHeap* GetDescriptorHeap(const SR_DescriptorType& aDescriptorType) const;

    static SR_RenderDevice* gInstance;

protected:
    bool mEnableDebugMode;
    bool mEnableBreakOnError;
};

//ProjectFilter(Interface)
#pragma once

#include "SR_Format.h"
#include "SR_RenderEnums.h"
#include "SR_DescriptorHeap.h"
#include "SR_Texture.h"
#include "SR_BufferView.h"
#include "SR_Shader.h"
#include "SR_PipelineState.h"
#include "SR_CommandQueue.h"
#include "SR_SwapChain.h"

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

	virtual SC_Ref<SR_SwapChain> CreateSwapChain(const SR_SwapChainProperties& aProperties, void* aNativeWindowHandle);

    const SR_API& GetAPI() const;
    
    static bool Create(const SR_API& aAPIType);
    static void Destroy();

    static SR_RenderDevice* gInstance;

protected:

    SR_API mRenderApi;

    bool mEnableDebugMode;
    bool mEnableBreakOnError;
};

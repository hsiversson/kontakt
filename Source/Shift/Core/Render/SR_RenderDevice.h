//ProjectFilter(Interface)
#pragma once

#include "SR_Format.h"
#include "SR_RenderEnums.h"
#include "SR_DescriptorHeap.h"
#include "SR_Texture.h"
#include "SR_Buffer.h"
#include "SR_Shader.h"
#include "SR_PipelineState.h"
#include "SR_CommandQueue.h"
#include "SR_SwapChain.h"
#include "SR_DeviceCapabilities.h"
#include "SR_ShaderCompiler.h"

class SR_RenderDevice
{
public:
    SR_RenderDevice();
    virtual ~SR_RenderDevice();

    virtual bool Init() = 0;

    void BeginFrame();
    void EndFrame();
    void Present();

	virtual SC_Ref<SR_TextureResource> CreateTextureResource(const SR_TextureResourceProperties& aTextureResourceProperties, const SR_PixelData* aInitialData = nullptr, uint32 aDataCount = 0);
	virtual SC_Ref<SR_Texture> CreateTexture(const SR_TextureProperties& aTextureProperties, const SC_Ref<SR_TextureResource>& aResource);

	virtual SC_Ref<SR_BufferResource> CreateBufferResource(const SR_BufferResourceProperties& aBufferResourceProperties, const void* aInitialData = nullptr);
	virtual SC_Ref<SR_Buffer> CreateBuffer(const SR_BufferProperties& aBufferProperties, const SC_Ref<SR_BufferResource>& aResource);

    virtual SC_Ref<SR_Shader> CreateShader(const SR_CreateShaderProperties& aCreateShaderProperties);
    virtual SC_Ref<SR_PipelineState> CreatePipelineState();

	virtual SR_DescriptorHeap* GetDescriptorHeap(const SR_DescriptorHeapType& aDescriptorHeapType) const;

	virtual SC_Ref<SR_SwapChain> CreateSwapChain(const SR_SwapChainProperties& aProperties, void* aNativeWindowHandle);

    const SR_API& GetAPI() const;

	SR_CommandQueue* GetCommandQueue(const SR_CommandListType& aType) const;
    SR_RootSignature* GetRootSignature(const SR_RootSignatureType& aType) const;
    SR_ShaderCompiler* GetShaderCompiler() const;
    
    SR_SwapChain* GetCurrentSwapChain() const;
    void SetCurrentSwapChain(SR_SwapChain* aSwapChain);

    static bool Create(const SR_API& aAPIType);
    static void Destroy();

public:
    SR_DeviceCapabilities mCaps;

    static SR_RenderDevice* gInstance;

protected:

    bool PostInit();

    SR_API mRenderApi;

    SC_Ref<SR_SwapChain> mCurrentSwapChain;

    SC_Ptr<SR_ShaderCompiler> mShaderCompiler;

	SC_Ref<SR_CommandQueue> mCommandQueues[static_cast<uint32>(SR_CommandListType::COUNT)];
    SC_StaticArray<SC_Ref<SR_RootSignature>, SR_RootSignatureType_COUNT> mRootSignatures;

    bool mEnableDebugMode;
    bool mEnableBreakOnError;
};

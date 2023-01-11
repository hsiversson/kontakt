//ProjectFilter(DX12)
#pragma once

#if SR_ENABLE_DX12
#include "SR_RenderDevice.h"

#define SR_ENABLE_NVAPI		(1)
#define SR_ENABLE_AGS		(1)

struct ID3D12Device;
struct ID3D12Device5;
struct ID3D12Device6;

struct IDXGIFactory1;
struct IDXGIAdapter;
struct IDXGIAdapter3;

struct ID3D12InfoQueue;

class SR_CommandQueue_DX12;

class SR_RenderDevice_DX12 final : public SR_RenderDevice
{
public:
    SR_RenderDevice_DX12();
    ~SR_RenderDevice_DX12();

    bool Init() override;

	SC_Ref<SR_CommandList> CreateCommandList(const SR_CommandListType& aType) override;

	SC_Ref<SR_TextureResource> CreateTextureResource(const SR_TextureResourceProperties& aTextureResourceProperties, const SR_PixelData* aInitialData = nullptr, uint32 aDataCount = 0) override;
	SC_Ref<SR_Texture> CreateTexture(const SR_TextureProperties& aTextureProperties, const SC_Ref<SR_TextureResource>& aResource) override;

	SC_Ref<SR_BufferResource> CreateBufferResource(const SR_BufferResourceProperties& aBufferResourceProperties, const void* aInitialData = nullptr) override;
	SC_Ref<SR_Buffer> CreateBuffer(const SR_BufferProperties& aBufferProperties, const SC_Ref<SR_BufferResource>& aResource) override;

	SC_Ref<SR_Shader> CreateShader(const SR_CreateShaderProperties& aCreateShaderProperties) override;
	SC_Ref<SR_PipelineState> CreatePipelineState() override;

	SC_Ref<SR_FenceResource> CreateFenceResource() override;

	SR_DescriptorHeap* GetDescriptorHeap(const SR_DescriptorHeapType& aDescriptorHeapType) const override;

	SC_Ref<SR_SwapChain> CreateSwapChain(const SR_SwapChainProperties& aProperties, void* aNativeWindowHandle) override;

	ID3D12Device* GetD3D12Device() const;
	ID3D12Device5* GetD3D12Device5() const;
	ID3D12Device6* GetD3D12Device6() const;
	IDXGIFactory1* GetDXGIFactory1() const;

	static SR_RenderDevice_DX12* gInstance;

private:
	bool DetermineAdapter();
	bool QueryDeviceCapabilites();
	bool CreateCommandQueues();
	bool CreateDescriptorHeaps();
	bool SetupRootSignatures();

private:
    SR_ComPtr<ID3D12Device> mD3D12Device;
	SR_ComPtr<ID3D12Device5> mD3D12Device5;
	SR_ComPtr<ID3D12Device6> mD3D12Device6;
	SR_ComPtr<IDXGIFactory1> mDXGIFactory1;
	SR_ComPtr<IDXGIAdapter> mDXGIAdapter;
	SR_ComPtr<IDXGIAdapter3> mDXGIAdapter3;

	SR_ComPtr<ID3D12InfoQueue> mD3D12InfoQueue;

	SR_DescriptorHeap* mDefaultDescriptorHeap;
	SR_DescriptorHeap* mSamplerDescriptorHeap;
	SR_DescriptorHeap* mRTVDescriptorHeap;
	SR_DescriptorHeap* mDSVDescriptorHeap;

    bool mEnableGpuValidation;

#if SR_ENABLE_DRED
    bool mEnableDRED;
#endif
};

#endif
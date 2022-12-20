//ProjectFilter(DX12)
#include "Render_Precompiled.h"

#if SR_ENABLE_DX12
#include "SR_RenderDevice_DX12.h"
#include "SR_TextureResource_DX12.h"
#include "SR_Texture_DX12.h"
#include "SR_SwapChain_DX12.h"
#include "SR_CommandQueue_DX12.h"
#include "SR_DescriptorHeap_DX12.h"
#include "SR_DirectXShaderCompiler.h"
#include "SR_PipelineState_DX12.h"
#include "SR_RootSignature_DX12.h"

#if IS_PC_PLATFORM
	#if SR_ENABLE_NVAPI
		#include "nvapi.h"
	#endif
	#if SR_ENABLE_AGS
		#include "amd_ags.h"
	#endif
#endif

extern "C" { __declspec(dllexport) extern const UINT D3D12SDKVersion = 606; }
extern "C" { __declspec(dllexport) extern const char* D3D12SDKPath = "./"; }

SR_RenderDevice_DX12* SR_RenderDevice_DX12::gInstance = nullptr;

SR_RenderDevice_DX12::SR_RenderDevice_DX12()
	: mEnableGpuValidation(false)
#if SR_ENABLE_DRED
	, mEnableDRED(false)
#endif
{
	mRenderApi = SR_API::D3D12;

	gInstance = this;
}

SR_RenderDevice_DX12::~SR_RenderDevice_DX12()
{
	gInstance = nullptr;
}

bool SR_RenderDevice_DX12::Init()
{
	if (mEnableDebugMode)
	{
		SC_LOG("D3D12 Debug Layer: Enabled");
		SR_ComPtr<ID3D12Debug> debugger;
		D3D12GetDebugInterface(IID_PPV_ARGS(&debugger));
		debugger->EnableDebugLayer();

		SR_ComPtr<ID3D12Debug6> debugger6;
		debugger->QueryInterface(IID_PPV_ARGS(&debugger6));
		if (debugger6)
			debugger6->SetEnableAutoName(true);
	}

	if (mEnableGpuValidation)
	{
		SC_LOG("D3D12 GPU-based Validation: Enabled");
		SR_ComPtr<ID3D12Debug1> debugger;
		D3D12GetDebugInterface(IID_PPV_ARGS(&debugger));
		debugger->SetEnableGPUBasedValidation(true);
		debugger->SetEnableSynchronizedCommandQueueValidation(true);

	}

#if SR_ENABLE_DRED
	if (mEnableDRED)
	{
		SC_LOG("D3D12 DRED: Enabled");
		SR_ComPtr<ID3D12DeviceRemovedExtendedDataSettings1> dredSettings;
		D3D12GetDebugInterface(IID_PPV_ARGS(&dredSettings));
		dredSettings->SetAutoBreadcrumbsEnablement(D3D12_DRED_ENABLEMENT_FORCED_ON);
		dredSettings->SetPageFaultEnablement(D3D12_DRED_ENABLEMENT_FORCED_ON);
	}
#endif

	DetermineAdapter();

	SC_LOG("Creating D3D12Device.");
	HRESULT hr = D3D12CreateDevice(mDXGIAdapter.Get(), D3D_FEATURE_LEVEL_12_0, IID_PPV_ARGS(&mD3D12Device));

	hr = mD3D12Device.As(&mD3D12Device5);
	hr = mD3D12Device.As(&mD3D12Device6);

	if (!QueryDeviceCapabilites())
		return false;

	if (mEnableDebugMode)
	{
		if (SUCCEEDED(mD3D12Device->QueryInterface(IID_PPV_ARGS(&mD3D12InfoQueue))))
		{
			D3D12_MESSAGE_SEVERITY severities[] =
			{
				D3D12_MESSAGE_SEVERITY_INFO
			};
			D3D12_MESSAGE_ID denyIds[] =
			{
				D3D12_MESSAGE_ID_CLEARRENDERTARGETVIEW_MISMATCHINGCLEARVALUE,
				D3D12_MESSAGE_ID_CLEARDEPTHSTENCILVIEW_MISMATCHINGCLEARVALUE
			};

			D3D12_INFO_QUEUE_FILTER newFilter = {};
			newFilter.DenyList.NumSeverities = _countof(severities);
			newFilter.DenyList.pSeverityList = severities;
			newFilter.DenyList.NumIDs = _countof(denyIds);
			newFilter.DenyList.pIDList = denyIds;
			mD3D12InfoQueue->PushStorageFilter(&newFilter);
			if (mEnableBreakOnError)
			{
				mD3D12InfoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_CORRUPTION, true);
				mD3D12InfoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_ERROR, true);
			}
		}
	}

	mShaderCompiler = new SR_DirectXShaderCompiler(SR_DirectXShaderCompiler::Backend::DXIL);

	if (!CreateCommandQueues())
		return false;

	if (!CreateDescriptorHeaps())
		return false;

	if (!SetupRootSignatures())
		return false;

	return true;
}

SC_Ref<SR_TextureResource> SR_RenderDevice_DX12::CreateTextureResource(const SR_TextureResourceProperties& aTextureResourceProperties, const SR_PixelData* aInitialData, uint32 aDataCount)
{
	SC_Ref<SR_TextureResource_DX12> newTextureResource = new SR_TextureResource_DX12(aTextureResourceProperties);

	if (!newTextureResource->Init(aInitialData, aDataCount))
		return nullptr;

	return newTextureResource;
}

SC_Ref<SR_Texture> SR_RenderDevice_DX12::CreateTexture(const SR_TextureProperties& aTextureProperties, const SC_Ref<SR_TextureResource>& aResource)
{
	SC_Ref<SR_Texture_DX12> newTexture = new SR_Texture_DX12(aTextureProperties, aResource);

	if (!newTexture->Init())
		return nullptr;

	return newTexture;
}

SC_Ref<SR_Shader> SR_RenderDevice_DX12::CreateShader(const SR_CreateShaderProperties& aCreateShaderProperties)
{
	SC_Ref<SR_Shader> shader = new SR_Shader();

	SR_ShaderCompileArgs args;
	args.mEntryPoint = aCreateShaderProperties.mEntryPoint;
	args.mShaderFile = aCreateShaderProperties.mFileName;
	args.mType = aCreateShaderProperties.mType;

	if (!mShaderCompiler->CompileFromFile(args, shader->mShaderByteCode, &shader->mMetaData))
	{
		SC_ERROR("Failed to compile shader.");
		return nullptr;
	}

	return shader;
}

SC_Ref<SR_PipelineState> SR_RenderDevice_DX12::CreatePipelineState()
{
	SC_Ref<SR_PipelineState_DX12> pso = new SR_PipelineState_DX12();

	SR_PipelineStateProperties psoProps;
	if (!pso->Init(psoProps))
		return nullptr;

	return pso;
}

SR_CommandQueue* SR_RenderDevice_DX12::GetCommandQueue(const SR_CommandListType& aType) const
{
	return mCommandQueues[static_cast<uint32>(aType)];
}

SR_DescriptorHeap* SR_RenderDevice_DX12::GetDescriptorHeap(const SR_DescriptorHeapType& aDescriptorHeapType) const
{
	switch (aDescriptorHeapType)
	{
	case SR_DescriptorHeapType::CBV_SRV_UAV:
		return mDefaultDescriptorHeap;

	case SR_DescriptorHeapType::RTV:
		return mRTVDescriptorHeap;

	case SR_DescriptorHeapType::DSV:
		return mDSVDescriptorHeap;

	case SR_DescriptorHeapType::SAMPLER:
		return mSamplerDescriptorHeap;

	default:
		return nullptr;
	}
}

SC_Ref<SR_SwapChain> SR_RenderDevice_DX12::CreateSwapChain(const SR_SwapChainProperties& aProperties, void* aNativeWindowHandle)
{
	SC_Ref<SR_SwapChain_DX12> newSwapChain = new SR_SwapChain_DX12();

	if (!newSwapChain->Init(aProperties, aNativeWindowHandle))
		return nullptr;

	return newSwapChain;
}

ID3D12Device* SR_RenderDevice_DX12::GetD3D12Device() const
{
	return mD3D12Device.Get();
}

ID3D12Device5* SR_RenderDevice_DX12::GetD3D12Device5() const
{
	return mD3D12Device5.Get();
}

ID3D12Device6* SR_RenderDevice_DX12::GetD3D12Device6() const
{
	return mD3D12Device6.Get();
}

IDXGIFactory1* SR_RenderDevice_DX12::GetDXGIFactory1() const
{
	return mDXGIFactory1.Get();
}

bool SR_RenderDevice_DX12::DetermineAdapter()
{
	HRESULT hr = CreateDXGIFactory1(IID_PPV_ARGS(&mDXGIFactory1));
	if (!SR_VerifyHRESULT(hr))
		return false;

	SR_ComPtr<IDXGIAdapter1> tempAdapter;
	DXGI_ADAPTER_DESC1 adapterDesc = {};
	SC_SizeT adapterScore = 0;
	for (uint32 i = 0; mDXGIFactory1->EnumAdapters1(i, &tempAdapter) != DXGI_ERROR_NOT_FOUND; ++i)
	{
		DXGI_ADAPTER_DESC1 desc = {};
		tempAdapter->GetDesc1(&desc);

		if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE)
			continue;

		SC_SizeT score = desc.DedicatedVideoMemory;

		if (adapterDesc.VendorId == 0x10DE ||	// Nvidia
			adapterDesc.VendorId == 0x1002 ||	// AMD
			adapterDesc.VendorId == 0x163C ||	// Intel
			adapterDesc.VendorId == 0x8086)		// Intel
		{
			score *= 4;
		}

		if (score > adapterScore)
		{
			adapterDesc = desc;
			adapterScore = score;
			mDXGIAdapter = tempAdapter;
		}
	}

	{
		if (adapterDesc.VendorId == 0x10DE)
		{
			mCaps.mDeviceInfo.mVendor = SR_GpuVendor::Nvidia;
			SC_LOG("Graphics Vendor: Nvidia");
		}
		else if (adapterDesc.VendorId == 0x1002)
		{
			mCaps.mDeviceInfo.mVendor = SR_GpuVendor::AMD;
			SC_LOG("Graphics Vendor: AMD");
		}
		else if (adapterDesc.VendorId == 0x163C || adapterDesc.VendorId == 0x8086)
		{
			mCaps.mDeviceInfo.mVendor = SR_GpuVendor::Intel;
			SC_LOG("Graphics Vendor: Intel");
		}

		hr = mDXGIAdapter.As(&mDXGIAdapter3);
		if (!SR_VerifyHRESULT(hr))
			return false;

		mCaps.mDeviceInfo.mDeviceName = SC_UTF::ToUTF8(adapterDesc.Description);
		mCaps.mDeviceInfo.mDedicatedVRAM = uint32(adapterDesc.DedicatedVideoMemory >> 20);

		SC_LOG("Graphics card: {0} (id: {1} rev: {2})", mCaps.mDeviceInfo.mDeviceName.c_str(), adapterDesc.DeviceId, adapterDesc.Revision);
		SC_LOG("Video Memory: {0}MB", mCaps.mDeviceInfo.mDedicatedVRAM);
	}

	return true;
}

bool SR_RenderDevice_DX12::QueryDeviceCapabilites()
{
	{
#if IS_PC_PLATFORM
	#if SR_ENABLE_NVAPI
		if (mCaps.mDeviceInfo.mVendor == SR_GpuVendor::Nvidia && !SC_CommandLine::HasCommand("nonvapi"))
		{
			if (NvAPI_Initialize() == NVAPI_OK)
			{
				NvU32 driverVersion;
				NvAPI_ShortString driverString;
				if (NvAPI_SYS_GetDriverAndBranchVersion(&driverVersion, driverString) == NVAPI_OK)
				{
					mCaps.mDeviceInfo.mDriverVersion = driverVersion;
					mCaps.mDeviceInfo.mDriverVersionString = driverString;
					SC_LOG("NvAPI: Driver: {} (Driver String: {})", driverVersion, driverString);
				}

				DXGI_ADAPTER_DESC1 adapterDesc = {};
				mDXGIAdapter3->GetDesc1(&adapterDesc);

				NvPhysicalGpuHandle nvGPUHandles[NVAPI_MAX_PHYSICAL_GPUS];
				NvU32 numGPUs = 0;
				if (NvAPI_EnumPhysicalGPUs(nvGPUHandles, &numGPUs) == NVAPI_OK)
				{
					for (uint32 i = 0; i < numGPUs; ++i)
					{
						NvPhysicalGpuHandle& gpuHandle = nvGPUHandles[i];
						NvU32 deviceId = 0;
						NvU32 subSystemId = 0;
						NvU32 revisionId = 0;
						NvU32 extDeviceId = 0;
						if (NvAPI_GPU_GetPCIIdentifiers(gpuHandle, &deviceId, &subSystemId, &revisionId, &extDeviceId) == NVAPI_OK)
						{
							if (extDeviceId == adapterDesc.DeviceId && revisionId == adapterDesc.Revision && subSystemId == adapterDesc.SubSysId)
							{
								NvAPI_ShortString fullName;
								if (NvAPI_GPU_GetFullName(gpuHandle, fullName) == NVAPI_OK)
									SC_LOG("NvAPI: {}", fullName);

								NvU32 coreCount = 0;
								if (NvAPI_GPU_GetGpuCoreCount(gpuHandle, &coreCount) == NVAPI_OK)
								{
									SC_LOG("NvAPI: Num Shader Cores: {}", coreCount);
									mCaps.mDeviceInfo.mNumShaderCores = coreCount;
								}

								NV_GPU_ARCH_INFO architectureInfo;
								architectureInfo.version = NV_GPU_ARCH_INFO_VER;
								if (NvAPI_GPU_GetArchInfo(gpuHandle, &architectureInfo) == NVAPI_OK)
								{
									switch (architectureInfo.architecture_id)
									{
									case NV_GPU_ARCHITECTURE_GK100:
									case NV_GPU_ARCHITECTURE_GK110:
									case NV_GPU_ARCHITECTURE_GK200:
										mCaps.mDeviceInfo.mArchitecture = SR_GpuArchitecture::Nv_Kepler;
										SC_LOG("NvAPI: Gpu Architecture: Kepler");
										break;
									case NV_GPU_ARCHITECTURE_GM000:
									case NV_GPU_ARCHITECTURE_GM200:
										mCaps.mDeviceInfo.mArchitecture = SR_GpuArchitecture::Nv_Maxwell;
										SC_LOG("NvAPI: Gpu Architecture: Maxwell");
										break;
									case NV_GPU_ARCHITECTURE_GP100:
										mCaps.mDeviceInfo.mArchitecture = SR_GpuArchitecture::Nv_Pascal;
										SC_LOG("NvAPI: Gpu Architecture: Pascal");
										break;
									case NV_GPU_ARCHITECTURE_TU100:
										mCaps.mDeviceInfo.mArchitecture = SR_GpuArchitecture::Nv_Turing;
										SC_LOG("NvAPI: Gpu Architecture: Turing");
										break;
									case NV_GPU_ARCHITECTURE_GV100:
									case NV_GPU_ARCHITECTURE_GV110:
										mCaps.mDeviceInfo.mArchitecture = SR_GpuArchitecture::Nv_Volta;
										SC_LOG("NvAPI: Gpu Architecture: Volta");
										break;
									case NV_GPU_ARCHITECTURE_GA100:
										mCaps.mDeviceInfo.mArchitecture = SR_GpuArchitecture::Nv_Ampere;
										SC_LOG("NvAPI: Gpu Architecture: Ampere");
										break;
									default:
										break;
									}
								}

								break;
							}
						}
					}
				}
			}
		}
	#endif //SR_ENABLE_NVAPI

	#if SR_ENABLE_AGS
		if (mCaps.mDeviceInfo.mVendor == SR_GpuVendor::AMD && !SC_CommandLine::HasCommand("noags"))
		{
			AGSConfiguration config = {};
			AGSGPUInfo gpuInfo = {};
			AGSReturnCode status = agsInitialize(AGS_MAKE_VERSION(AMD_AGS_VERSION_MAJOR, AMD_AGS_VERSION_MINOR, AMD_AGS_VERSION_PATCH), &config, nullptr, &gpuInfo);
			if (status == AGS_SUCCESS)
			{
				//gUsingAGS = true;

			}
		}
	#endif //SR_ENABLE_AGS
#endif //IS_PC_PLATFORM
	}

	{
		mCaps.mAsyncCompute = !SC_CommandLine::HasCommand("noasynccompute");
		SC_LOG("Async Compute: {}", mCaps.mAsyncCompute ? "true" : "false");

		mCaps.mAsyncCopy = !SC_CommandLine::HasCommand("noasynccopy");
		SC_LOG("Async Copy: {}", mCaps.mAsyncCopy ? "true" : "false");
	}

	HRESULT hr = S_OK;
	{
		D3D12_FEATURE_DATA_SHADER_MODEL shaderModel = {};
		shaderModel.HighestShaderModel = D3D_SHADER_MODEL_6_7;
		hr = mD3D12Device->CheckFeatureSupport(D3D12_FEATURE_SHADER_MODEL, &shaderModel, sizeof(shaderModel));
		while (hr == E_INVALIDARG && shaderModel.HighestShaderModel > D3D_SHADER_MODEL_6_0)
		{
			shaderModel.HighestShaderModel = D3D_SHADER_MODEL(shaderModel.HighestShaderModel - 1);
			hr = mD3D12Device->CheckFeatureSupport(D3D12_FEATURE_SHADER_MODEL, &shaderModel, sizeof(shaderModel));
		}
		mCaps.mHighestShaderModel = SR_ConvertShaderModel_DX12(shaderModel.HighestShaderModel);
		//SC_LOG("Shader Model: {}", GetShaderModelString(mCaps.mHighestShaderModel));
	}
	{
		D3D12_FEATURE_DATA_D3D12_OPTIONS dx12Options = {};
		hr = mD3D12Device->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS, &dx12Options, sizeof(dx12Options));
		if (!SR_VerifyHRESULT(hr))
		{
			SC_ERROR("Could not check options from device");
			return false;
		}
		mCaps.mConservativeRasterization = dx12Options.ConservativeRasterizationTier > D3D12_CONSERVATIVE_RASTERIZATION_TIER_NOT_SUPPORTED;
		SC_LOG("Conservative Rasterization: {}", mCaps.mConservativeRasterization ? "true" : "false");
	}
	{
		D3D12_FEATURE_DATA_D3D12_OPTIONS5 dx12Options5 = {};
		hr = mD3D12Device->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS5, &dx12Options5, sizeof(dx12Options5));
		if (!SR_VerifyHRESULT(hr))
		{
			SC_ERROR("Could not check Options5 from device");
			return false;
		}
		mCaps.mRaytracing = dx12Options5.RaytracingTier > D3D12_RAYTRACING_TIER_NOT_SUPPORTED;
		mCaps.mInlineRaytracing = dx12Options5.RaytracingTier > D3D12_RAYTRACING_TIER_1_0;
		SC_LOG("Raytracing: {}", mCaps.mRaytracing ? "true" : "false");
		SC_LOG("Inline Raytracing: {}", mCaps.mInlineRaytracing ? "true" : "false");
	}
	{
		D3D12_FEATURE_DATA_D3D12_OPTIONS6 dx12Options6 = {};
		hr = mD3D12Device->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS6, &dx12Options6, sizeof(dx12Options6));
		if (!SR_VerifyHRESULT(hr))
		{
			SC_ERROR("Could not check Options6 from device");
			return false;
		}
		mCaps.mVariableRateShading = dx12Options6.VariableShadingRateTier > D3D12_VARIABLE_SHADING_RATE_TIER_NOT_SUPPORTED;
		SC_LOG("Variable Rate Shading: {}", mCaps.mVariableRateShading ? "true" : "false");
	}
	{
		D3D12_FEATURE_DATA_D3D12_OPTIONS7 dx12Options7 = {};
		hr = mD3D12Device->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS7, &dx12Options7, sizeof(dx12Options7));
		if (!SR_VerifyHRESULT(hr))
		{
			SC_ERROR("Could not check Options7 from device");
			return false;
		}
		mCaps.mMeshShaders = dx12Options7.MeshShaderTier > D3D12_MESH_SHADER_TIER_NOT_SUPPORTED;
		mCaps.mSamplerFeedback = dx12Options7.SamplerFeedbackTier > D3D12_SAMPLER_FEEDBACK_TIER_NOT_SUPPORTED;
		SC_LOG("Mesh Shaders: {}", mCaps.mMeshShaders ? "true" : "false");
		SC_LOG("Sampler Feedback: {}", mCaps.mSamplerFeedback ? "true" : "false");
	}
	return true;
}

bool SR_RenderDevice_DX12::CreateCommandQueues()
{
	for (uint32 type = 0; type < static_cast<uint32>(SR_CommandListType::COUNT); ++type)
	{
		mCommandQueues[type] = new SR_CommandQueue_DX12();
		if (!mCommandQueues[type]->Init(static_cast<SR_CommandListType>(type)))
			return false;
	}

	return true;
}

bool SR_RenderDevice_DX12::CreateDescriptorHeaps()
{
	mDefaultDescriptorHeap = new SR_DescriptorHeap_DX12(512*1024, SR_DescriptorHeapType::CBV_SRV_UAV, true);
	mSamplerDescriptorHeap = new SR_DescriptorHeap_DX12(128, SR_DescriptorHeapType::SAMPLER, true);
	mRTVDescriptorHeap = new SR_DescriptorHeap_DX12(512, SR_DescriptorHeapType::RTV);
	mDSVDescriptorHeap = new SR_DescriptorHeap_DX12(16, SR_DescriptorHeapType::DSV);

	return true;
}

bool SR_RenderDevice_DX12::SetupRootSignatures()
{
	SR_RootSignatureProperties properties;
	
	// TEMP 2 root cbvs
	for (uint32 i = 0; i < 2; ++i)
	{
		SR_RootParam& param = properties.mRootParams.Add();
		param.InitAsDescriptor(i, 0, SR_RootParamVisibility::All, SR_RootParamType::CBV);
	}
	SR_StaticSamplerProperties samplerProps;
	samplerProps.mVisibility = SR_RootParamVisibility::All;
	samplerProps.mProperties.mBorderColor = SC_Vector4(0);
	samplerProps.mProperties.mComparison = SR_ComparisonFunc::Never;
	samplerProps.mProperties.mLODBias = 0.f;
	samplerProps.mProperties.mMaxAnisotropy = 0;
	samplerProps.mProperties.mMinFilter = SR_FilterMode::Point;
	samplerProps.mProperties.mMagFilter = SR_FilterMode::Point;
	samplerProps.mProperties.mMipFilter = SR_FilterMode::Point;
	samplerProps.mProperties.mWrapX = SR_WrapMode::Clamp;
	samplerProps.mProperties.mWrapY = SR_WrapMode::Clamp;
	samplerProps.mProperties.mWrapZ = SR_WrapMode::Clamp;
	properties.mStaticSamplers.Add(samplerProps);  // Point Clamp

	samplerProps.mProperties.mWrapX = SR_WrapMode::Wrap;
	samplerProps.mProperties.mWrapY = SR_WrapMode::Wrap;
	samplerProps.mProperties.mWrapZ = SR_WrapMode::Wrap;
	properties.mStaticSamplers.Add(samplerProps); // Point Wrap

	samplerProps.mProperties.mWrapX = SR_WrapMode::Mirror;
	samplerProps.mProperties.mWrapY = SR_WrapMode::Mirror;
	samplerProps.mProperties.mWrapZ = SR_WrapMode::Mirror;
	properties.mStaticSamplers.Add(samplerProps); // Point Mirror

	samplerProps.mProperties.mMinFilter = SR_FilterMode::Linear;
	samplerProps.mProperties.mMagFilter = SR_FilterMode::Linear;
	samplerProps.mProperties.mMipFilter = SR_FilterMode::Point;
	samplerProps.mProperties.mWrapX = SR_WrapMode::Clamp;
	samplerProps.mProperties.mWrapY = SR_WrapMode::Clamp;
	samplerProps.mProperties.mWrapZ = SR_WrapMode::Clamp;
	properties.mStaticSamplers.Add(samplerProps);  // Bilinear Clamp

	samplerProps.mProperties.mWrapX = SR_WrapMode::Wrap;
	samplerProps.mProperties.mWrapY = SR_WrapMode::Wrap;
	samplerProps.mProperties.mWrapZ = SR_WrapMode::Wrap;
	properties.mStaticSamplers.Add(samplerProps); // Bilinear Wrap

	samplerProps.mProperties.mWrapX = SR_WrapMode::Mirror;
	samplerProps.mProperties.mWrapY = SR_WrapMode::Mirror;
	samplerProps.mProperties.mWrapZ = SR_WrapMode::Mirror;
	properties.mStaticSamplers.Add(samplerProps); // Bilinear Mirror

	samplerProps.mProperties.mMinFilter = SR_FilterMode::Linear;
	samplerProps.mProperties.mMagFilter = SR_FilterMode::Linear;
	samplerProps.mProperties.mMipFilter = SR_FilterMode::Linear;
	samplerProps.mProperties.mWrapX = SR_WrapMode::Clamp;
	samplerProps.mProperties.mWrapY = SR_WrapMode::Clamp;
	samplerProps.mProperties.mWrapZ = SR_WrapMode::Clamp;
	properties.mStaticSamplers.Add(samplerProps);  // Trilinear Clamp

	samplerProps.mProperties.mWrapX = SR_WrapMode::Wrap;
	samplerProps.mProperties.mWrapY = SR_WrapMode::Wrap;
	samplerProps.mProperties.mWrapZ = SR_WrapMode::Wrap;
	properties.mStaticSamplers.Add(samplerProps); // Trilinear Wrap

	samplerProps.mProperties.mWrapX = SR_WrapMode::Mirror;
	samplerProps.mProperties.mWrapY = SR_WrapMode::Mirror;
	samplerProps.mProperties.mWrapZ = SR_WrapMode::Mirror;
	properties.mStaticSamplers.Add(samplerProps); // Trilinear Mirror

	samplerProps.mProperties.mMinFilter = SR_FilterMode::Linear;
	samplerProps.mProperties.mMagFilter = SR_FilterMode::Linear;
	samplerProps.mProperties.mMipFilter = SR_FilterMode::Linear;
	samplerProps.mProperties.mMaxAnisotropy = 16;
	samplerProps.mProperties.mWrapX = SR_WrapMode::Clamp;
	samplerProps.mProperties.mWrapY = SR_WrapMode::Clamp;
	samplerProps.mProperties.mWrapZ = SR_WrapMode::Clamp;
	properties.mStaticSamplers.Add(samplerProps);  // Anisotropic Clamp

	samplerProps.mProperties.mWrapX = SR_WrapMode::Wrap;
	samplerProps.mProperties.mWrapY = SR_WrapMode::Wrap;
	samplerProps.mProperties.mWrapZ = SR_WrapMode::Wrap;
	properties.mStaticSamplers.Add(samplerProps); // Anisotropic Wrap

	samplerProps.mProperties.mWrapX = SR_WrapMode::Mirror;
	samplerProps.mProperties.mWrapY = SR_WrapMode::Mirror;
	samplerProps.mProperties.mWrapZ = SR_WrapMode::Mirror;
	properties.mStaticSamplers.Add(samplerProps); // Anisotropic Mirror

	{
		properties.mFlags = SR_RootSignatureFlag_DefaultSetup;
		properties.mFlags |= SR_RootSignatureFlag_DescriptorHeapDirectAccess;
		properties.mFlags |= SR_RootSignatureFlag_SamplerHeapDirectAccess;
		SC_Ref<SR_RootSignature_DX12> rootSig = new SR_RootSignature_DX12(properties);

		if (!rootSig->Init())
			return false;

		mRootSignatures[static_cast<uint32>(SR_RootSignatureType::Graphics)] = rootSig;
	}
	{
		properties.mFlags = SR_RootSignatureFlag_MeshShaderSetup;
		properties.mFlags |= SR_RootSignatureFlag_DescriptorHeapDirectAccess;
		properties.mFlags |= SR_RootSignatureFlag_SamplerHeapDirectAccess;
		SC_Ref<SR_RootSignature_DX12> rootSig = new SR_RootSignature_DX12(properties);

		if (!rootSig->Init())
			return false;

		mRootSignatures[static_cast<uint32>(SR_RootSignatureType::GraphicsMS)] = rootSig;
	}
	{
		properties.mFlags = SR_RootSignatureFlag_ComputeSetup;
		properties.mFlags |= SR_RootSignatureFlag_DescriptorHeapDirectAccess;
		properties.mFlags |= SR_RootSignatureFlag_SamplerHeapDirectAccess;
		properties.mIsCompute = true;
		SC_Ref<SR_RootSignature_DX12> rootSig = new SR_RootSignature_DX12(properties);

		if (!rootSig->Init())
			return false;

		mRootSignatures[static_cast<uint32>(SR_RootSignatureType::Compute)] = rootSig;
	}
#if SR_ENABLE_RAYTRACING
	{
		properties.mFlags = SR_RootSignatureFlag_ComputeSetup;
		properties.mFlags |= SR_RootSignatureFlag_DescriptorHeapDirectAccess;
		properties.mFlags |= SR_RootSignatureFlag_SamplerHeapDirectAccess;
		properties.mIsCompute = true;
		SC_Ref<SR_RootSignature_DX12> rootSig = new SR_RootSignature_DX12(properties);

		if (!rootSig->Init())
			return false;
		mRootSignatures[static_cast<uint32>(SR_RootSignatureType::Raytracing)] = rootSig;
	}
#endif
	return true;
}

#endif
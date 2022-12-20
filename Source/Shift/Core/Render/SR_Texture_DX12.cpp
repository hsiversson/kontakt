//ProjectFilter(DX12/Resources)
#include "Render_Precompiled.h"

#if SR_ENABLE_DX12
#include "SR_Texture_DX12.h"
#include "SR_RenderDevice_DX12.h"
#include "SR_TextureResource_DX12.h"

SR_Texture_DX12::SR_Texture_DX12(const SR_TextureProperties& aProperties, const SC_Ref<SR_TextureResource>& aTextureResource)
	: SR_Texture(aProperties, aTextureResource)
{
	mDX12Resource = static_cast<SR_TextureResource_DX12*>(GetResource());
}

SR_Texture_DX12::~SR_Texture_DX12()
{

}

bool SR_Texture_DX12::Init()
{
	if ((mProperties.mBindFlags & SR_TextureBindFlag_Texture) && !InitSRV())
		return false;

	if ((mProperties.mBindFlags & SR_TextureBindFlag_RWTexture) && !InitUAV())
		return false;

	if ((mProperties.mBindFlags & SR_TextureBindFlag_RenderTarget) && !InitRTV())
		return false;

	if ((mProperties.mBindFlags & SR_TextureBindFlag_DepthStencil) && !InitDSV())
		return false;

	return true;
}

D3D12_CPU_DESCRIPTOR_HANDLE SR_Texture_DX12::GetCPUHandle(const SR_TextureDescriptorType& aDescriptorType) const
{
	const SR_Descriptor& descriptor = mDescriptors[static_cast<uint32>(aDescriptorType)];
	return D3D12_CPU_DESCRIPTOR_HANDLE{descriptor.mDescriptorHandleCPU};
}

D3D12_GPU_DESCRIPTOR_HANDLE SR_Texture_DX12::GetGPUHandle(const SR_TextureDescriptorType& aDescriptorType) const
{
	const SR_Descriptor& descriptor = mDescriptors[static_cast<uint32>(aDescriptorType)];
	return D3D12_GPU_DESCRIPTOR_HANDLE{descriptor.mDescriptorHandleGPU};
}

bool SR_Texture_DX12::InitSRV()
{
	const SR_TextureResourceProperties& resourceProps = mResource->GetProperties();

	D3D12_SHADER_RESOURCE_VIEW_DESC desc = {};
	desc.Format = SR_ConvertToValidSRVFormat_DX12(SR_ConvertFormat_DX12(mProperties.mFormat));
	desc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;

	bool isArray = resourceProps.mArraySize > 0;
	uint32 mip = mProperties.mMostDetailedMip;
	uint32 numMips = mProperties.mNumMips ? mProperties.mNumMips : resourceProps.mNumMips - mip;

	uint32 resourceArraySize = (resourceProps.mType == SR_ResourceType::Texture3D) ? resourceProps.mSize.z : SC_Max(resourceProps.mArraySize, 1U);
	uint32 arraySize = mProperties.mArraySize ? mProperties.mArraySize : resourceArraySize - mProperties.mFirstArrayIndex;

	switch (mProperties.mDimension)
	{
	case SR_TextureDimension::Texture1D:
		desc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE1D;
		desc.Texture1D.MostDetailedMip = mip;
		desc.Texture1D.MipLevels = numMips;
		break;
	case SR_TextureDimension::Texture2D:
		if (isArray)
		{
			desc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2DARRAY;
			desc.Texture2DArray.MostDetailedMip = mip;
			desc.Texture2DArray.MipLevels = numMips;
			desc.Texture2DArray.FirstArraySlice = mProperties.mFirstArrayIndex;
			desc.Texture2DArray.ArraySize = arraySize;
		}
		else
		{
			desc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
			desc.Texture2D.MostDetailedMip = mip;
			desc.Texture2D.MipLevels = numMips;
		}
		break;
	case SR_TextureDimension::Texture3D:
		desc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE3D;
		desc.Texture3D.MostDetailedMip = mip;
		desc.Texture3D.MipLevels = numMips;
		break;
	case SR_TextureDimension::TextureCube:
		desc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURECUBE;
		desc.TextureCube.MipLevels = numMips;
		desc.TextureCube.MostDetailedMip = mip;
		break;
	default:
		SC_ASSERT(false, "Unknown dimension");
		return false;
	}

	SR_Descriptor descriptor = SR_RenderDevice_DX12::gInstance->GetDescriptorHeap(SR_DescriptorHeapType::CBV_SRV_UAV)->Alloc();
	SR_RenderDevice_DX12::gInstance->GetD3D12Device()->CreateShaderResourceView(mDX12Resource->mD3D12Resource, &desc, D3D12_CPU_DESCRIPTOR_HANDLE{ descriptor.mDescriptorHandleCPU });
	mDescriptors[(uint32)SR_TextureDescriptorType::Texture] = descriptor;
	return true;
}

bool SR_Texture_DX12::InitUAV()
{
	const SR_TextureResourceProperties& resourceProps = mResource->GetProperties();

	D3D12_UNORDERED_ACCESS_VIEW_DESC desc = {};
	desc.Format = SR_ConvertFormat_DX12(mProperties.mFormat);

	bool isArray = resourceProps.mArraySize > 0;
	uint32 mip = mProperties.mMostDetailedMip;
	uint32 resourceArraySize = (resourceProps.mType == SR_ResourceType::Texture3D) ? resourceProps.mSize.z : SC_Max(resourceProps.mArraySize, 1U);
	uint32 arraySize = mProperties.mArraySize ? mProperties.mArraySize : resourceArraySize - mProperties.mFirstArrayIndex;

	switch (mProperties.mDimension)
	{
	case SR_TextureDimension::Texture1D:
		desc.ViewDimension = D3D12_UAV_DIMENSION_TEXTURE1D;
		desc.Texture1D.MipSlice = mip;
		break;
	case SR_TextureDimension::Texture2D:
		if (isArray)
		{
			desc.ViewDimension = D3D12_UAV_DIMENSION_TEXTURE2DARRAY;
			desc.Texture2DArray.MipSlice = mip;
			desc.Texture2DArray.FirstArraySlice = mProperties.mFirstArrayIndex;
			desc.Texture2DArray.ArraySize = arraySize;
		}
		else
		{
			desc.ViewDimension = D3D12_UAV_DIMENSION_TEXTURE2D;
			desc.Texture2D.MipSlice = mip;
		}
		break;
	case SR_TextureDimension::Texture3D:
		desc.ViewDimension = D3D12_UAV_DIMENSION_TEXTURE3D;
		desc.Texture3D.MipSlice = mip;
		desc.Texture3D.FirstWSlice = mProperties.mFirstArrayIndex;
		desc.Texture3D.WSize = arraySize;
		break;
	case SR_TextureDimension::TextureCube:
		desc.ViewDimension = D3D12_UAV_DIMENSION_TEXTURE2DARRAY;
		desc.Texture2DArray.MipSlice = mip;
		desc.Texture2DArray.FirstArraySlice = mProperties.mFirstArrayIndex * 6;
		desc.Texture2DArray.ArraySize = SC_Max(arraySize, 1U) * 6;
		break;
	default:
		SC_ASSERT(false, "Unknown dimension");
		return false;
	}

	SR_Descriptor descriptor = SR_RenderDevice_DX12::gInstance->GetDescriptorHeap(SR_DescriptorHeapType::UAV)->Alloc();
	SR_RenderDevice_DX12::gInstance->GetD3D12Device()->CreateUnorderedAccessView(mDX12Resource->mD3D12Resource, nullptr, &desc, D3D12_CPU_DESCRIPTOR_HANDLE{ descriptor.mDescriptorHandleCPU });
	mDescriptors[(uint32)SR_TextureDescriptorType::RWTexture] = descriptor;
	return true;
}

bool SR_Texture_DX12::InitRTV()
{
	const SR_TextureResourceProperties& resourceProps = mResource->GetProperties();

	D3D12_RENDER_TARGET_VIEW_DESC desc = {};
	desc.Format = SR_ConvertFormat_DX12(mProperties.mFormat);

	bool isArray = resourceProps.mArraySize > 1;
	//if (resourceProps.mIsCubeMap)
	//	arraySize *= 6;

	switch (resourceProps.mType)
	{
	case SR_ResourceType::Texture1D:
		desc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE1D;
		break;
	case SR_ResourceType::Texture2D:
		if (isArray)
		{
			desc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2DARRAY;
			desc.Texture2DArray.ArraySize = 1;
			desc.Texture2DArray.FirstArraySlice = mProperties.mFirstArrayIndex + 0/*mProperties.mFace*/;
			desc.Texture2DArray.MipSlice = mProperties.mNumMips;
		}
		else
		{
			desc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;
			desc.Texture2D.MipSlice = mProperties.mNumMips;
		}
		break;
	case SR_ResourceType::Texture3D:
		desc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE3D;
		break;
	default:
		SC_ASSERT(false, "Dimension not supported.");
		return false;
	}

	SR_Descriptor descriptor = SR_RenderDevice_DX12::gInstance->GetDescriptorHeap(SR_DescriptorHeapType::RTV)->Alloc();
	SR_RenderDevice_DX12::gInstance->GetD3D12Device()->CreateRenderTargetView(mDX12Resource->mD3D12Resource, &desc, D3D12_CPU_DESCRIPTOR_HANDLE{ descriptor.mDescriptorHandleCPU });
	mDescriptors[(uint32)SR_TextureDescriptorType::RenderTarget] = descriptor;
	return true;
}

bool SR_Texture_DX12::InitDSV()
{
	const SR_TextureResourceProperties& resourceProps = mResource->GetProperties();

	D3D12_DEPTH_STENCIL_VIEW_DESC desc = {};
	desc.Format = SR_ConvertFormat_DX12(mProperties.mFormat);

	bool isArray = resourceProps.mArraySize > 0;
	uint32 mip = mProperties.mMostDetailedMip;
	uint32 resourceArraySize = (resourceProps.mType == SR_ResourceType::Texture3D) ? resourceProps.mSize.z : SC_Max(resourceProps.mArraySize, 1U);
	uint32 arraySize = mProperties.mArraySize ? mProperties.mArraySize : resourceArraySize - mProperties.mFirstArrayIndex;

	switch (resourceProps.mType)
	{
	case SR_ResourceType::Texture1D:
		desc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE1D;
		desc.Texture1D.MipSlice = mip;
		break;
	case SR_ResourceType::Texture2D:
		if (isArray)
		{
			desc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2DARRAY;
			desc.Texture2DArray.ArraySize = arraySize;
			desc.Texture2DArray.FirstArraySlice = mProperties.mFirstArrayIndex;
			desc.Texture2DArray.MipSlice = mip;
		}
		else
		{
			desc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
			desc.Texture2D.MipSlice = mip;
		}
		break;
	default:
		SC_ASSERT(false, "Dimension not supported.");
		return false;
	}

	SR_Descriptor descriptor = SR_RenderDevice_DX12::gInstance->GetDescriptorHeap(SR_DescriptorHeapType::DSV)->Alloc();
	SR_RenderDevice_DX12::gInstance->GetD3D12Device()->CreateDepthStencilView(mDX12Resource->mD3D12Resource, &desc, D3D12_CPU_DESCRIPTOR_HANDLE{ descriptor.mDescriptorHandleCPU });
	mDescriptors[(uint32)SR_TextureDescriptorType::DepthStencil] = descriptor;
	return true;
}
#endif
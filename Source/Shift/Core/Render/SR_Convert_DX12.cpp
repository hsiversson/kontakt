//ProjectFilter(DX12)
#include "Render_Precompiled.h"

#if SR_ENABLE_DX12
#include "SR_Convert_DX12.h"
#include "SR_TextureResource.h"

SR_Format SR_ConvertFormat_DX12(DXGI_FORMAT aFormat)
{
	switch (aFormat)
	{
	case DXGI_FORMAT_R32G32B32A32_TYPELESS:		return SR_Format::RGBA32_TYPELESS;
	case DXGI_FORMAT_R32G32B32A32_FLOAT:		return SR_Format::RGBA32_FLOAT;
	case DXGI_FORMAT_R32G32B32A32_UINT:			return SR_Format::RGBA32_UINT;
	case DXGI_FORMAT_R32G32B32A32_SINT:			return SR_Format::RGBA32_SINT;
	case DXGI_FORMAT_R32G32B32_TYPELESS:		return SR_Format::RGB32_TYPELESS;
	case DXGI_FORMAT_R32G32B32_FLOAT:			return SR_Format::RGB32_FLOAT;
	case DXGI_FORMAT_R32G32B32_UINT:			return SR_Format::RGB32_UINT;
	case DXGI_FORMAT_R32G32B32_SINT:			return SR_Format::RGB32_SINT;
	case DXGI_FORMAT_R16G16B16A16_TYPELESS:		return SR_Format::RGBA16_TYPELESS;
	case DXGI_FORMAT_R16G16B16A16_FLOAT:		return SR_Format::RGBA16_FLOAT;
	case DXGI_FORMAT_R16G16B16A16_UNORM:		return SR_Format::RGBA16_UNORM;
	case DXGI_FORMAT_R16G16B16A16_UINT:			return SR_Format::RGBA16_UINT;
	case DXGI_FORMAT_R16G16B16A16_SNORM:		return SR_Format::RGBA16_SNORM;
	case DXGI_FORMAT_R16G16B16A16_SINT:			return SR_Format::RGBA16_SINT;
	case DXGI_FORMAT_R8G8B8A8_TYPELESS:			return SR_Format::RGBA8_TYPELESS;
	case DXGI_FORMAT_R8G8B8A8_UNORM:			return SR_Format::RGBA8_UNORM;
	case DXGI_FORMAT_R8G8B8A8_UNORM_SRGB:		return SR_Format::RGBA8_UNORM_SRGB;
	case DXGI_FORMAT_R8G8B8A8_UINT:				return SR_Format::RGBA8_UINT;
	case DXGI_FORMAT_R8G8B8A8_SNORM:			return SR_Format::RGBA8_SNORM;
	case DXGI_FORMAT_R8G8B8A8_SINT:				return SR_Format::RGBA8_SINT;
	case DXGI_FORMAT_B8G8R8A8_UNORM:			return SR_Format::BGRA8_UNORM;
	case DXGI_FORMAT_R10G10B10A2_TYPELESS:		return SR_Format::RGB10A2_TYPELESS;
	case DXGI_FORMAT_R10G10B10A2_UNORM:			return SR_Format::RGB10A2_UNORM;
	case DXGI_FORMAT_R10G10B10A2_UINT:			return SR_Format::RGB10A2_UINT;
	case DXGI_FORMAT_R11G11B10_FLOAT:			return SR_Format::RG11B10_FLOAT;
	case DXGI_FORMAT_R32G32_TYPELESS:			return SR_Format::RG32_TYPELESS;
	case DXGI_FORMAT_R32G32_FLOAT:				return SR_Format::RG32_FLOAT;
	case DXGI_FORMAT_R32G32_UINT:				return SR_Format::RG32_UINT;
	case DXGI_FORMAT_R32G32_SINT:				return SR_Format::RG32_SINT;
	case DXGI_FORMAT_D32_FLOAT_S8X24_UINT:		return SR_Format::D32_FLOAT_S8X24_UINT;
	case DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS:	return SR_Format::R32_FLOAT_X8X24_TYPELESS;
	case DXGI_FORMAT_X32_TYPELESS_G8X24_UINT:	return SR_Format::X32_TYPELESS_G8X24_UINT;
	case DXGI_FORMAT_R16G16_TYPELESS:			return SR_Format::RG16_TYPELESS;
	case DXGI_FORMAT_R16G16_FLOAT:				return SR_Format::RG16_FLOAT;
	case DXGI_FORMAT_R16G16_UNORM:				return SR_Format::RG16_UNORM;
	case DXGI_FORMAT_R16G16_UINT:				return SR_Format::RG16_UINT;
	case DXGI_FORMAT_R16G16_SNORM:				return SR_Format::RG16_SNORM;
	case DXGI_FORMAT_R16G16_SINT:				return SR_Format::RG16_SINT;
	case DXGI_FORMAT_R8G8_TYPELESS:				return SR_Format::RG8_TYPELESS;
	case DXGI_FORMAT_R8G8_UNORM:				return SR_Format::RG8_UNORM;
	case DXGI_FORMAT_R8G8_UINT:					return SR_Format::RG8_UINT;
	case DXGI_FORMAT_R8G8_SNORM:				return SR_Format::RG8_SNORM;
	case DXGI_FORMAT_R8G8_SINT:					return SR_Format::RG8_SINT;
	case DXGI_FORMAT_R32_TYPELESS:				return SR_Format::R32_TYPELESS;
	case DXGI_FORMAT_R32_FLOAT:					return SR_Format::R32_FLOAT;
	case DXGI_FORMAT_D32_FLOAT:					return SR_Format::D32_FLOAT;
	case DXGI_FORMAT_R32_UINT:					return SR_Format::R32_UINT;
	case DXGI_FORMAT_R32_SINT:					return SR_Format::R32_SINT;
	case DXGI_FORMAT_R16_TYPELESS:				return SR_Format::R16_TYPELESS;
	case DXGI_FORMAT_R16_FLOAT:					return SR_Format::R16_FLOAT;
	case DXGI_FORMAT_R16_UNORM:					return SR_Format::R16_UNORM;
	case DXGI_FORMAT_D16_UNORM:					return SR_Format::D16_UNORM;
	case DXGI_FORMAT_R16_UINT:					return SR_Format::R16_UINT;
	case DXGI_FORMAT_R16_SNORM:					return SR_Format::R16_SNORM;
	case DXGI_FORMAT_R16_SINT:					return SR_Format::R16_SINT;
	case DXGI_FORMAT_R8_TYPELESS:				return SR_Format::R8_TYPELESS;
	case DXGI_FORMAT_R8_UNORM:					return SR_Format::R8_UNORM;
	case DXGI_FORMAT_R8_UINT:					return SR_Format::R8_UINT;
	case DXGI_FORMAT_R8_SNORM:					return SR_Format::R8_SNORM;
	case DXGI_FORMAT_BC1_UNORM:					return SR_Format::BC1_UNORM;
	case DXGI_FORMAT_BC2_UNORM:					return SR_Format::BC2_UNORM;
	case DXGI_FORMAT_BC3_UNORM:					return SR_Format::BC3_UNORM;
	case DXGI_FORMAT_BC4_UNORM:					return SR_Format::BC4_UNORM;
	case DXGI_FORMAT_BC4_SNORM:					return SR_Format::BC4_SNORM;
	case DXGI_FORMAT_BC5_UNORM:					return SR_Format::BC5_UNORM;
	case DXGI_FORMAT_BC5_SNORM:					return SR_Format::BC5_SNORM;
	case DXGI_FORMAT_BC7_UNORM:					return SR_Format::BC7;
	case DXGI_FORMAT_BC7_UNORM_SRGB:			return SR_Format::BC7_SRGB;

	case DXGI_FORMAT_UNKNOWN:
	default:
		return SR_Format::UNKNOWN;
	}
}

DXGI_FORMAT SR_ConvertFormat_DX12(SR_Format aFormat)
{
	switch (aFormat)
	{
	case SR_Format::RGBA32_TYPELESS:			return DXGI_FORMAT_R32G32B32A32_TYPELESS;
	case SR_Format::RGBA32_FLOAT:				return DXGI_FORMAT_R32G32B32A32_FLOAT;
	case SR_Format::RGBA32_UINT:				return DXGI_FORMAT_R32G32B32A32_UINT;
	case SR_Format::RGBA32_SINT:				return DXGI_FORMAT_R32G32B32A32_SINT;
	case SR_Format::RGB32_TYPELESS:				return DXGI_FORMAT_R32G32B32_TYPELESS;
	case SR_Format::RGB32_FLOAT:				return DXGI_FORMAT_R32G32B32_FLOAT;
	case SR_Format::RGB32_UINT:					return DXGI_FORMAT_R32G32B32_UINT;
	case SR_Format::RGB32_SINT:					return DXGI_FORMAT_R32G32B32_SINT;
	case SR_Format::RGBA16_TYPELESS:			return DXGI_FORMAT_R16G16B16A16_TYPELESS;
	case SR_Format::RGBA16_FLOAT:				return DXGI_FORMAT_R16G16B16A16_FLOAT;
	case SR_Format::RGBA16_UNORM:				return DXGI_FORMAT_R16G16B16A16_UNORM;
	case SR_Format::RGBA16_UINT:				return DXGI_FORMAT_R16G16B16A16_UINT;
	case SR_Format::RGBA16_SNORM:				return DXGI_FORMAT_R16G16B16A16_SNORM;
	case SR_Format::RGBA16_SINT:				return DXGI_FORMAT_R16G16B16A16_SINT;
	case SR_Format::RGBA8_TYPELESS:				return DXGI_FORMAT_R8G8B8A8_TYPELESS;
	case SR_Format::RGBA8_UNORM:				return DXGI_FORMAT_R8G8B8A8_UNORM;
	case SR_Format::RGBA8_UNORM_SRGB:			return DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	case SR_Format::RGBA8_UINT:					return DXGI_FORMAT_R8G8B8A8_UINT;
	case SR_Format::RGBA8_SNORM:				return DXGI_FORMAT_R8G8B8A8_SNORM;
	case SR_Format::RGBA8_SINT:					return DXGI_FORMAT_R8G8B8A8_SINT;
	case SR_Format::BGRA8_UNORM:				return DXGI_FORMAT_B8G8R8A8_UNORM;
	case SR_Format::RGB10A2_TYPELESS:			return DXGI_FORMAT_R10G10B10A2_TYPELESS;
	case SR_Format::RGB10A2_UNORM:				return DXGI_FORMAT_R10G10B10A2_UNORM;
	case SR_Format::RGB10A2_UINT:				return DXGI_FORMAT_R10G10B10A2_UINT;
	case SR_Format::RG11B10_FLOAT:				return DXGI_FORMAT_R11G11B10_FLOAT;
	case SR_Format::RG32_TYPELESS:				return DXGI_FORMAT_R32G32_TYPELESS;
	case SR_Format::RG32_FLOAT:					return DXGI_FORMAT_R32G32_FLOAT;
	case SR_Format::RG32_UINT:					return DXGI_FORMAT_R32G32_UINT;
	case SR_Format::RG32_SINT:					return DXGI_FORMAT_R32G32_SINT;
	case SR_Format::D32_FLOAT_S8X24_UINT:		return DXGI_FORMAT_D32_FLOAT_S8X24_UINT;
	case SR_Format::R32_FLOAT_X8X24_TYPELESS:	return DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS;
	case SR_Format::X32_TYPELESS_G8X24_UINT:	return DXGI_FORMAT_X32_TYPELESS_G8X24_UINT;
	case SR_Format::RG16_TYPELESS:				return DXGI_FORMAT_R16G16_TYPELESS;
	case SR_Format::RG16_FLOAT:					return DXGI_FORMAT_R16G16_FLOAT;
	case SR_Format::RG16_UNORM:					return DXGI_FORMAT_R16G16_UNORM;
	case SR_Format::RG16_UINT:					return DXGI_FORMAT_R16G16_UINT;
	case SR_Format::RG16_SNORM:					return DXGI_FORMAT_R16G16_SNORM;
	case SR_Format::RG16_SINT:					return DXGI_FORMAT_R16G16_SINT;
	case SR_Format::RG8_TYPELESS:				return DXGI_FORMAT_R8G8_TYPELESS;
	case SR_Format::RG8_UNORM:					return DXGI_FORMAT_R8G8_UNORM;
	case SR_Format::RG8_UINT:					return DXGI_FORMAT_R8G8_UINT;
	case SR_Format::RG8_SNORM:					return DXGI_FORMAT_R8G8_SNORM;
	case SR_Format::RG8_SINT:					return DXGI_FORMAT_R8G8_SINT;
	case SR_Format::R32_TYPELESS:				return DXGI_FORMAT_R32_TYPELESS;
	case SR_Format::R32_FLOAT:					return DXGI_FORMAT_R32_FLOAT;
	case SR_Format::D32_FLOAT:					return DXGI_FORMAT_D32_FLOAT;
	case SR_Format::R32_UINT:					return DXGI_FORMAT_R32_UINT;
	case SR_Format::R32_SINT:					return DXGI_FORMAT_R32_SINT;
	case SR_Format::R16_TYPELESS:				return DXGI_FORMAT_R16_TYPELESS;
	case SR_Format::R16_FLOAT:					return DXGI_FORMAT_R16_FLOAT;
	case SR_Format::R16_UNORM:					return DXGI_FORMAT_R16G16_UNORM;
	case SR_Format::D16_UNORM:					return DXGI_FORMAT_D16_UNORM;
	case SR_Format::R16_UINT:					return DXGI_FORMAT_R16_UINT;
	case SR_Format::R16_SNORM:					return DXGI_FORMAT_R16_SNORM;
	case SR_Format::R16_SINT:					return DXGI_FORMAT_R16_SINT;
	case SR_Format::R8_TYPELESS:				return DXGI_FORMAT_R8_TYPELESS;
	case SR_Format::R8_UNORM:					return DXGI_FORMAT_R8_UNORM;
	case SR_Format::R8_UINT:					return DXGI_FORMAT_R8_UINT;
	case SR_Format::R8_SNORM:					return DXGI_FORMAT_R8_SNORM;
	case SR_Format::R8_SINT:					return DXGI_FORMAT_R8_SINT;
	case SR_Format::BC1_UNORM:					return DXGI_FORMAT_BC1_UNORM;
	case SR_Format::BC2_UNORM:					return DXGI_FORMAT_BC2_UNORM;
	case SR_Format::BC3_UNORM:					return DXGI_FORMAT_BC3_UNORM;
	case SR_Format::BC4_UNORM:					return DXGI_FORMAT_BC4_UNORM;
	case SR_Format::BC4_SNORM:					return DXGI_FORMAT_BC4_SNORM;
	case SR_Format::BC5_UNORM:					return DXGI_FORMAT_BC5_UNORM;
	case SR_Format::BC5_SNORM:					return DXGI_FORMAT_BC5_SNORM;
	case SR_Format::BC7:						return DXGI_FORMAT_BC7_UNORM;
	case SR_Format::BC7_SRGB:					return DXGI_FORMAT_BC7_UNORM_SRGB;
	
	case SR_Format::UNKNOWN:	
	default:
		return DXGI_FORMAT_UNKNOWN;
	}
}

DXGI_FORMAT SR_ConvertToValidSRVFormat_DX12(DXGI_FORMAT aFormat)
{
	switch (aFormat)
	{
	case DXGI_FORMAT_D32_FLOAT: 	return DXGI_FORMAT_R32_FLOAT;
	case DXGI_FORMAT_D16_UNORM: 	return DXGI_FORMAT_R16_UNORM;
	}
	return aFormat;
}

D3D12_RESOURCE_DESC SR_GetResourceDesc_DX12(const SR_TextureResourceProperties& aProperties)
{
	D3D12_RESOURCE_DESC resourceDesc = {};
	resourceDesc.Width = static_cast<UINT64>(aProperties.mSize.x);
	resourceDesc.Height = static_cast<UINT64>(aProperties.mSize.y);
	resourceDesc.DepthOrArraySize = static_cast<UINT16>(SC_Max(aProperties.mArraySize, 1U));
	if (aProperties.mType == SR_ResourceType::Texture3D)
		resourceDesc.DepthOrArraySize = static_cast<UINT16>(aProperties.mSize.z);
	//else if (aProperties.mType == SR_ResourceType::Texture2D && aProperties.mIsCubeMap)
	//	resourceDesc.DepthOrArraySize *= 6;

	resourceDesc.Format = SR_ConvertFormat_DX12(aProperties.mFormat);
	resourceDesc.MipLevels = aProperties.mNumMips;
	resourceDesc.Dimension = SR_ConvertDimension_DX12(aProperties.mType);
	resourceDesc.SampleDesc.Count = 1;
	resourceDesc.SampleDesc.Quality = 0;
	resourceDesc.Flags = D3D12_RESOURCE_FLAG_NONE;
	resourceDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
	resourceDesc.Alignment = D3D12_DEFAULT_RESOURCE_PLACEMENT_ALIGNMENT;

	if (aProperties.mAllowRenderTarget)
		resourceDesc.Flags |= D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET;
	if (aProperties.mAllowDepthStencil)
		resourceDesc.Flags |= D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;
	if (aProperties.mAllowWrites)
		resourceDesc.Flags |= D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS;

	return resourceDesc;
}

D3D12_RESOURCE_DESC SR_GetResourceDesc_DX12(const SR_BufferResourceProperties& /*aProperties*/)
{
	D3D12_RESOURCE_DESC resourceDesc = {};
	return resourceDesc;
}

D3D12_RESOURCE_DIMENSION SR_ConvertDimension_DX12(const SR_ResourceType& aType)
{
	switch (aType)
	{
	case SR_ResourceType::Texture1D: return D3D12_RESOURCE_DIMENSION_TEXTURE1D;
	case SR_ResourceType::Texture2D: return D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	case SR_ResourceType::Texture3D: return D3D12_RESOURCE_DIMENSION_TEXTURE3D;
	case SR_ResourceType::Buffer:	 return D3D12_RESOURCE_DIMENSION_BUFFER;

	case SR_ResourceType::Unknown:
	default:
		return D3D12_RESOURCE_DIMENSION_UNKNOWN;
	}
}

#endif
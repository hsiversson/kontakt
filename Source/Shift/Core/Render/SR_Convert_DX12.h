//ProjectFilter(DX12)
#pragma once

#if SR_ENABLE_DX12
#include "SR_Format.h"
#include "SR_RenderEnums.h"

struct SR_TextureResourceProperties;
struct SR_BufferResourceProperties;

SR_Format					SR_ConvertFormat_DX12(DXGI_FORMAT aFormat);
DXGI_FORMAT					SR_ConvertFormat_DX12(SR_Format aFormat);
DXGI_FORMAT					SR_ConvertToValidSRVFormat_DX12(DXGI_FORMAT aFormat);

D3D12_RESOURCE_DESC			SR_GetResourceDesc_DX12(const SR_TextureResourceProperties& aProperties);
D3D12_RESOURCE_DESC			SR_GetResourceDesc_DX12(const SR_BufferResourceProperties& aProperties);

D3D12_RESOURCE_DIMENSION	SR_ConvertDimension_DX12(const SR_ResourceType& aType);

//D3D12_RESOURCE_STATES		SR_D3D12ConvertResourceState(uint32 aState);
//SR_ResourceState			SR_D3D12ConvertResourceState(D3D12_RESOURCE_STATES aState);
D3D12_CULL_MODE				SR_ConvertCullMode_DX12(SR_CullMode aCullMode);
D3D12_COMPARISON_FUNC		SR_ConvertComparisonFunc_DX12(SR_ComparisonFunc aComparisonFunc);
D3D12_STENCIL_OP			SR_ConvertStencilOperator_DX12(SR_StencilOperator aStencilOperator);
D3D12_BLEND					SR_ConvertBlendMode_DX12(SR_BlendMode aBlendMode);
D3D12_BLEND_OP				SR_ConvertBlendFunc_DX12(SR_BlendFunc aBlendFunc);
UINT8						SR_ConvertColorWriteMask_DX12(uint8 aWriteMask);
SR_ShaderModel				SR_ConvertShaderModel_DX12(D3D_SHADER_MODEL aShaderModel);
D3D_SHADER_MODEL			SR_ConvertShaderModel_DX12(SR_ShaderModel aShaderModel);
D3D12_FILTER				SR_ConvertFilter_DX12(SR_FilterMode aMinFilter, SR_FilterMode aMagFilter, SR_FilterMode aMipFilter, SR_ComparisonFunc aCompareFunc, uint32 aAnisotropy);
D3D12_TEXTURE_ADDRESS_MODE	SR_ConvertWrapMode_DX12(SR_WrapMode aWrapMode);

#endif


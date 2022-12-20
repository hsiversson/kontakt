//ProjectFilter(DX12/Shader)
#pragma once

#if SR_ENABLE_DX12
#include "SR_PipelineState.h"

class SR_BufferResource;
class SR_PipelineState_DX12 final : public SR_PipelineState
{
public:
	SR_PipelineState_DX12();
	~SR_PipelineState_DX12();

	bool Init(const SR_PipelineStateProperties& aProperties);

	ID3D12PipelineState* GetD3D12PipelineState() const;
#if SR_ENABLE_RAYTRACING
	const D3D12_DISPATCH_RAYS_DESC& GetDispatchRaysDesc() const;
	ID3D12StateObject* GetD3D12StateObject() const;
#endif

private:
	bool InitDefault(const SR_PipelineStateProperties& aProperties);
#if SR_ENABLE_MESH_SHADERS
	bool InitAsMeshShader(const SR_PipelineStateProperties& aProperties);
#endif
	bool InitAsComputeShader(const SR_PipelineStateProperties& aProperties);
#if SR_ENABLE_RAYTRACING
	bool InitAsRaytracingShader(const SR_PipelineStateProperties& aProperties);
	void CreateRaytracingShaderTable(const SR_PipelineStateProperties& aProperties);
#endif

	SR_ComPtr<ID3D12PipelineState> mD3D12PipelineState;
#if SR_ENABLE_RAYTRACING
	D3D12_DISPATCH_RAYS_DESC mDispatchRaysDesc;
	SR_ComPtr<ID3D12StateObject> mD3D12StateObject;
	SC_Ref<SR_BufferResource> mRaytracingShaderTable;
#endif
};

#endif
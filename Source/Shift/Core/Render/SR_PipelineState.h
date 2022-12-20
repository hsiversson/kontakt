//ProjectFilter(Interface/Shader)
#pragma once
#include "SR_Resource.h"
#include "SR_Shader.h"
#include "SR_RootSignature.h"
#include "SR_VertexLayout.h"
#include "SR_RenderStates.h"

struct SR_PipelineStateProperties
{
	SC_StaticArray<SR_CreateShaderProperties, SR_ShaderType_COUNT> mCreateShaderProperties;
	SR_VertexLayout mVertexLayout;

	SR_RasterizerStateProperties mRasterizerProperties;
	SR_BlendStateProperties mBlendStateProperties;
	SR_DepthStencilStateProperties mDepthStencilProperties;
	SR_RenderTargetFormats mRenderTargetFormats;
	SR_PrimitiveTopology mPrimitiveTopology;

	SC_Ref<SR_RootSignature> mRootSignature;
};

class SR_RootSignature;
class SR_PipelineState : public SR_Resource
{
public:
	SR_PipelineState();
	virtual ~SR_PipelineState();

	const bool IsMeshShader() const;
	const bool IsComputeShader() const;
	const bool IsRaytracingShader() const;

	SR_RootSignature* GetRootSignature() const;

	const SR_ShaderMetaData& GetShaderMetaData(const SR_ShaderType& aShaderType);

protected:
	SC_Ref<SR_Shader> mShaders[SR_ShaderType_COUNT];

	SR_RootSignature* mRootSignature;
	bool mIsMeshShader : 1;
	bool mIsComputeShader : 1;
	bool mIsRaytracingShader : 1;
};


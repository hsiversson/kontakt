//ProjectFilter(Interface/Shader)
#include "Render_Precompiled.h"
#include "SR_PipelineState.h"

SR_PipelineState::SR_PipelineState()
	: mRootSignature(nullptr)
	, mIsMeshShader(false)
	, mIsComputeShader(false)
	, mIsRaytracingShader(false)
{

}

SR_PipelineState::~SR_PipelineState()
{

}

const bool SR_PipelineState::IsMeshShader() const
{
	return mIsMeshShader;
}

const bool SR_PipelineState::IsComputeShader() const
{
	return mIsComputeShader;
}

const bool SR_PipelineState::IsRaytracingShader() const
{
	return mIsRaytracingShader;
}

SR_RootSignature* SR_PipelineState::GetRootSignature() const
{
	return mRootSignature;
}

const SR_ShaderMetaData& SR_PipelineState::GetShaderMetaData(const SR_ShaderType& aShaderType)
{
	return mShaders[static_cast<uint32>(aShaderType)]->GetMetaData();
}

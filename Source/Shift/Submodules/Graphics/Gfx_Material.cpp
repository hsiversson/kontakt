#include "Graphics_Precompiled.h"
#include "Gfx_Material.h"

Gfx_Material::Gfx_Material()
	: mType(Gfx_MaterialType::Default)
	, mShadingModel(Gfx_MaterialShadingModel::Default)
	, mBlendMode(Gfx_MaterialBlendMode::Opaque)
	, mWriteMotionVectors(true)
{

}

Gfx_Material::~Gfx_Material()
{

}

void Gfx_Material::SetMaterialType(const Gfx_MaterialType& aType)
{
	mType = aType;
}

const Gfx_MaterialType Gfx_Material::GetMaterialType() const
{
	return mType;
}

void Gfx_Material::SetShadingModel(const Gfx_MaterialShadingModel& aShadingModel)
{
	mShadingModel = aShadingModel;
}

const Gfx_MaterialShadingModel& Gfx_Material::GetShadingModel() const
{
	return mShadingModel;
}

void Gfx_Material::SetBlendMode(const Gfx_MaterialBlendMode& aBlendMode)
{
	mBlendMode = aBlendMode;
}

const Gfx_MaterialBlendMode& Gfx_Material::GetBlendMode() const
{
	return mBlendMode;
}

bool Gfx_Material::WriteMotionVectors() const
{
	return mWriteMotionVectors;
}

SR_PipelineState* Gfx_Material::GetPipelineState(const SR_VertexLayout& aVertexLayout, bool aIsDepth, bool aIsMeshlet)
{
	PipelineStatesMap& pipelineStates = GetPipelineStatesMap(aIsDepth, aIsMeshlet);
	if (pipelineStates.count(aVertexLayout) == 0)
	{
		// Didn't find in existing map, create it.
		pipelineStates.insert(std::make_pair(aVertexLayout, nullptr)); // insert a nullptr for now, which will be replaced in the long task below.

		this->IncrementRef();
		auto CreatePipelineState = [this, aVertexLayout, aIsDepth, aIsMeshlet]()
		{
			//PipelineStatesMap& pipelineStates = GetPipelineStatesMap(aIsDepth, aIsMeshlet);


			this->DecrementRef();
		};
		SC_CreateLongTask(CreatePipelineState);
	}
	return pipelineStates[aVertexLayout];
}

Gfx_Material::PipelineStatesMap& Gfx_Material::GetPipelineStatesMap(bool aIsDepth, bool aIsMeshlet)
{
	if (aIsDepth)
	{
		if (aIsMeshlet)
			return mPipelineStates_DepthMeshlet;
		else
			return mPipelineStates_Depth;
	}
	else
	{
		if (aIsMeshlet)
			return mPipelineStates_DefaultMeshlet;
		else
			return mPipelineStates_Default;
	}
}

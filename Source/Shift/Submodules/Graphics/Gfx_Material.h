#pragma once

enum class Gfx_MaterialType
{
	Surface,
	Decal,
	Volume,
	PostProcess,

	Default = Surface,
};

enum class Gfx_MaterialShadingModel
{
	Flat,
	Default,
	Subsurface,
	ClearCoat,
	Hair,
	Eye,
	Cloth,

	COUNT
};

enum class Gfx_MaterialBlendMode
{
	Opaque,
	AlphaMasked,
	Translucent,
	Additive,

	COUNT
};

enum class Gfx_MaterialAttributes
{
	BaseColor,
	Normal,
	Roughness,
	Metallic,
	AmbientOcclusion,
	Specular,
	Opacity,
	EmissiveColor,
	RefractionIOR,
	ShadingModel,

	COUNT
};

class Gfx_Material : public SC_ReferenceCounted
{
	using PipelineStatesMap = SC_UnorderedMap<SR_VertexLayout, SC_Ref<SR_PipelineState>>;
public:
	Gfx_Material();
	~Gfx_Material();

	void SetMaterialType(const Gfx_MaterialType& aType);
	const Gfx_MaterialType GetMaterialType() const;

	void SetShadingModel(const Gfx_MaterialShadingModel& aShadingModel);
	const Gfx_MaterialShadingModel& GetShadingModel() const;

	void SetBlendMode(const Gfx_MaterialBlendMode& aBlendMode);
	const Gfx_MaterialBlendMode& GetBlendMode() const;

	bool WriteMotionVectors() const;

	SR_PipelineState* GetPipelineState(const SR_VertexLayout& aVertexLayout, bool aIsDepth, bool aIsMeshlet);

private:
	PipelineStatesMap& GetPipelineStatesMap(bool aIsDepth, bool aIsMeshlet);

	PipelineStatesMap mPipelineStates_Default;
	PipelineStatesMap mPipelineStates_DefaultMeshlet;
	PipelineStatesMap mPipelineStates_Depth;
	PipelineStatesMap mPipelineStates_DepthMeshlet;

	Gfx_MaterialType mType;
	Gfx_MaterialShadingModel mShadingModel;
	Gfx_MaterialBlendMode mBlendMode;

	bool mEnableRoughnessAA;
	bool mWriteMotionVectors;
};


//ProjectFilter(Lighting)
#pragma once

struct Gfx_DirectionalLightGpuData
{
	SC_Vector mDirection;
	float _unused;

	SC_Vector mColor;
	float mIntensity;

};

struct Gfx_LocalLightGpuData
{
	SC_Vector mPosition;
	float mRange;

	SC_Vector mColor;
	float mIntensity;

	SC_Vector mDirection;
	float mSourceRadius;

	float mInnerAngle;
	float mOuterAngle;
	uint32 mCastShadows;
	uint32 mShadowMapDescriptorIndex;

	uint32 mType;
	SC_Vector3i _unused;
};

class Gfx_Light
{
public:

private:

};


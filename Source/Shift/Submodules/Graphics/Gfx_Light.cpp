//ProjectFilter(Lighting)
#include "Graphics_Precompiled.h"
#include "Gfx_Light.h"

Gfx_Light::Gfx_Light(const Gfx_LightType& aType)
	: mType(aType)
	, mIntensity(1.0f)
	, mCastShadows(false)
{

}

Gfx_Light::~Gfx_Light()
{

}

const Gfx_LightType& Gfx_Light::GetType() const
{
	return mType;
}

void Gfx_Light::SetColor(const SC_Vector& aColor)
{
	mColor = aColor;
}

const SC_Vector& Gfx_Light::GetColor() const
{
	return mColor;
}

void Gfx_Light::SetIntensity(float aIntensity)
{
	mIntensity = aIntensity;
}

float Gfx_Light::GetIntensity() const
{
	return mIntensity;
}

void Gfx_Light::CastShadows(bool aValue)
{
	mCastShadows = aValue;
}

bool Gfx_Light::IsCastingShadows() const
{
	return mCastShadows;
}

Gfx_DirectionalLight::Gfx_DirectionalLight()
	: Gfx_Light(Gfx_LightType::Directional)
{

}

Gfx_DirectionalLight::~Gfx_DirectionalLight()
{

}

void Gfx_DirectionalLight::GetGpuData(Gfx_DirectionalLightGpuData& aOutGpuData) const
{
	aOutGpuData.mDirection = mDirection;
	aOutGpuData.mCastShadows = (uint32)mCastShadows;
	aOutGpuData.mColor = mColor;
	aOutGpuData.mIntensity = mIntensity;
}

void Gfx_DirectionalLight::SetDirection(const SC_Vector& aDirection)
{
	mDirection = aDirection;
	mDirection.Normalize();
}

const SC_Vector& Gfx_DirectionalLight::GetDirection() const
{
	return mDirection;
}

Gfx_PointLight::Gfx_PointLight(const Gfx_LightType& aType)
	: Gfx_Light(aType)
{

}

Gfx_PointLight::~Gfx_PointLight()
{

}

void Gfx_PointLight::GetGpuData(Gfx_LocalLightGpuData& aOutGpuData) const
{
	aOutGpuData.mPosition = mBoundingSphere.mCenter;
	aOutGpuData.mRange = mBoundingSphere.mRadius;
	aOutGpuData.mColor = mColor;
	aOutGpuData.mIntensity = mIntensity;
	aOutGpuData.mDirection = SC_Vector(0);
	aOutGpuData.mSourceRadius = mSourceRadius;
	aOutGpuData.mInnerAngle = 0.0f;
	aOutGpuData.mOuterAngle = 0.0f;
	aOutGpuData.mCastShadows = mCastShadows;
	aOutGpuData.mShadowMapDescriptorIndex = 0;
	aOutGpuData.mType = (uint32)mType;
}

const SC_Sphere& Gfx_PointLight::GetBoundingSphere() const
{
	return mBoundingSphere;
}

void Gfx_PointLight::SetPosition(const SC_Vector& aPosition)
{
	mBoundingSphere.mCenter = aPosition;
}

const SC_Vector& Gfx_PointLight::GetPosition() const
{
	return mBoundingSphere.mCenter;
}

void Gfx_PointLight::SetRange(float aRange)
{
	mBoundingSphere.mRadius = aRange;
}

float Gfx_PointLight::GetRange() const
{
	return mBoundingSphere.mRadius;
}

void Gfx_PointLight::SetSourceRadius(float aSourceRadius)
{
	mSourceRadius = aSourceRadius;
}

float Gfx_PointLight::GetSourceRadius() const
{
	return mSourceRadius;
}

Gfx_SpotLight::Gfx_SpotLight()
	: Gfx_PointLight(Gfx_LightType::Spot)
{

}

Gfx_SpotLight::~Gfx_SpotLight()
{

}

void Gfx_SpotLight::GetGpuData(Gfx_LocalLightGpuData& aOutGpuData) const
{
	aOutGpuData.mPosition = mBoundingSphere.mCenter;
	aOutGpuData.mRange = mBoundingSphere.mRadius;
	aOutGpuData.mColor = mColor;
	aOutGpuData.mIntensity = mIntensity;
	aOutGpuData.mDirection = mDirection;
	aOutGpuData.mSourceRadius = mSourceRadius;
	aOutGpuData.mInnerAngle = mInnerAngle;
	aOutGpuData.mOuterAngle = mOuterAngle;
	aOutGpuData.mCastShadows = mCastShadows;
	aOutGpuData.mShadowMapDescriptorIndex = 0;
	aOutGpuData.mType = (uint32)mType;
}

void Gfx_SpotLight::SetInnerAngle(float aAngle)
{
	mInnerAngle = aAngle;
}

float Gfx_SpotLight::GetInnerAngle() const
{
	return mInnerAngle;
}

void Gfx_SpotLight::SetOuterAngle(float aAngle)
{
	mOuterAngle = aAngle;
}

float Gfx_SpotLight::GetOuterAngle() const
{
	return mOuterAngle;
}

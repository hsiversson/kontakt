//ProjectFilter(Lighting)
#pragma once

enum class Gfx_LightType
{
	Directional,
	Point,
	Spot
};

struct Gfx_DirectionalLightGpuData
{
	SC_Vector mDirection;
	uint32 mCastShadows;

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

class Gfx_Light : public SC_ReferenceCounted
{
public:
	Gfx_Light(const Gfx_LightType& aType);
	virtual ~Gfx_Light();

	const Gfx_LightType& GetType() const;

	void SetColor(const SC_Vector& aColor);
	const SC_Vector& GetColor() const;

	void SetIntensity(float aIntensity);
	float GetIntensity() const;

	void CastShadows(bool aValue);
	bool IsCastingShadows() const;

	virtual void GetGpuData(Gfx_DirectionalLightGpuData&) const { SC_ASSERT(false); }
	virtual void GetGpuData(Gfx_LocalLightGpuData&) const { SC_ASSERT(false); }
protected:
	SC_Vector mColor;
	float mIntensity;
	bool mCastShadows;

	const Gfx_LightType mType;
};

class Gfx_DirectionalLight final : public Gfx_Light
{
public:
	Gfx_DirectionalLight();
	~Gfx_DirectionalLight();

	void GetGpuData(Gfx_DirectionalLightGpuData& aOutGpuData) const override;

	void SetDirection(const SC_Vector& aDirection);
	const SC_Vector& GetDirection() const;

private:
	SC_Vector mDirection;
};

class Gfx_PointLight : public Gfx_Light
{
public:
	Gfx_PointLight(const Gfx_LightType& aType = Gfx_LightType::Point);
	virtual ~Gfx_PointLight();

	virtual void GetGpuData(Gfx_LocalLightGpuData& aOutGpuData) const override;

	const SC_Sphere& GetBoundingSphere() const;

	void SetPosition(const SC_Vector& aPosition);
	const SC_Vector& GetPosition() const;

	void SetRange(float aRange);
	float GetRange() const;

	void SetSourceRadius(float aSourceRadius);
	float GetSourceRadius() const;

protected:
	SC_Sphere mBoundingSphere;
	float mSourceRadius;
};

class Gfx_SpotLight final : public Gfx_PointLight
{
public:
	Gfx_SpotLight();
	~Gfx_SpotLight();

	void GetGpuData(Gfx_LocalLightGpuData& aOutGpuData) const override;

	void SetInnerAngle(float aAngle);
	float GetInnerAngle() const;

	void SetOuterAngle(float aAngle);
	float GetOuterAngle() const;

private:
	SC_Vector mDirection;

	float mInnerAngle;
	float mOuterAngle;
};

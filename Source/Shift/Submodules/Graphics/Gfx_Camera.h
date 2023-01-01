//ProjectFilter(View)
#pragma once
#include "Gfx_Frustum.h"

class Gfx_Camera
{
public:
	Gfx_Camera();
	~Gfx_Camera();

	void SetPerspectiveProjection(const SC_Vector2& aSize, float aNear, float aFar, float aFov = 75.f);
	void SetOrthogonalProjection(const SC_Vector2& aSize, float aNear, float aFar);

	void SetViewportOffset(const SC_Vector2i& aOffset);

	void LookAt(const SC_Vector& aTargetPos, const SC_Vector& aUpVector = SC_Vector::gUpVector);

	void GetCornersOnPlane(float aZ, SC_Vector* aOutCorners) const;

	const Gfx_Frustum& GetFrustum() const;
	const SC_Vector& GetForward() const;
	const SC_Vector& GetUp() const;
	const SC_Vector& GetRight() const;
	const SC_Vector2& GetSize() const;
	float GetFov() const;
	float GetNear() const;
	float GetFar() const;
	float GetAspectRatio() const;

	SC_Vector GetPosition() const;

private:
	SC_Matrix mTransform;
	SC_Matrix mProjection;
	SC_Matrix mInvProjection;

	mutable Gfx_Frustum mFrustum;
	mutable SC_Vector mForward;
	mutable SC_Vector mUp;
	mutable SC_Vector mRight;

	SC_Vector2i mViewportOffset;
	SC_Vector2 mSize;
	float mFov;
	float mNear;
	float mFar;
	float mAspectRatio;

	bool mIsOrthogonal : 1;
};


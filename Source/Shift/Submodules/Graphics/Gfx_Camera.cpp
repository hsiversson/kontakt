//ProjectFilter(View)
#include "Graphics_Precompiled.h"
#include "Gfx_Camera.h"

Gfx_Camera::Gfx_Camera()
	: mFov(0.f)
	, mNear(0.f)
	, mFar(0.f)
	, mAspectRatio(0.f)
	, mIsOrthogonal(false)
{

}

Gfx_Camera::~Gfx_Camera()
{

}

void Gfx_Camera::SetPerspectiveProjection(const SC_Vector2& aSize, float aNear, float aFar, float aFov /*= 75.f*/)
{
	mProjection = SC_PerspectiveInvZMatrix(SC_DegreesToRadians(aFov * 0.5f), aSize.x, aSize.y, aNear, aFar);
	mInvProjection = mProjection.GetInversed();
	mSize = aSize;
	mNear = aNear;
	mFar = aFar;
	mFov = aFov;
	mAspectRatio = aSize.x / aSize.y;

	mIsOrthogonal = false;
}

void Gfx_Camera::SetOrthogonalProjection(const SC_Vector2& aSize, float aNear, float aFar)
{
	float zScale = 1.0f / (aFar - aNear);
	float zOffset = -aNear;
	mProjection = SC_OrthogonalInvZMatrix(aSize.x * 0.5f, aSize.y * 0.5f, zScale, zOffset);
	mInvProjection = mProjection.GetInversed();
	mSize = aSize;
	mNear = aNear;
	mFar = aFar;
	mFov = 0.f;

	mIsOrthogonal = true;
}

void Gfx_Camera::SetViewportOffset(const SC_Vector2i& aOffset)
{
	mViewportOffset = aOffset;
}

void Gfx_Camera::LookAt(const SC_Vector& aTargetPos, const SC_Vector& aUpVector /*= SC_Vector::gUpVector*/)
{
	SC_Vector pos = mTransform.GetPosition();
	SC_LookAtMatrix lookAtMatrix(pos, aTargetPos, aUpVector);
	mTransform = lookAtMatrix.GetInversed();
	mTransform.mAxisW = SC_Vector4(pos, mTransform.mAxisW.w);
}

void Gfx_Camera::GetCornersOnPlane(float aZ, SC_Vector* aOutCorners) const
{
	SC_ASSERT(aOutCorners != NULL);
	//if (mIsDirty)
	//	Update();

	float xScale = 0.0f;
	float yScale = 0.0f;
	if (mIsOrthogonal)
	{
		xScale = mSize.x * 0.5f;
		yScale = mSize.y * 0.5f;
	}
	else
	{
		xScale = aZ * SC_Tan(SC_DegreesToRadians(mFov) * 0.5f);
		yScale = xScale / mAspectRatio;
	}

	const SC_Vector axisX(1.0f, 0.0f, 0.0f);
	const SC_Vector axisY(0.0f, 1.0f, 0.0f);
	const SC_Vector axisZ(0.0f, 0.0f, 1.0f);
	aOutCorners[0] = (axisZ * aZ + axisY * yScale + axisX * xScale) * mTransform;
	aOutCorners[1] = (axisZ * aZ + axisY * yScale - axisX * xScale) * mTransform;
	aOutCorners[2] = (axisZ * aZ - axisY * yScale + axisX * xScale) * mTransform;
	aOutCorners[3] = (axisZ * aZ - axisY * yScale - axisX * xScale) * mTransform;
}

const Gfx_Frustum& Gfx_Camera::GetFrustum() const
{
	return mFrustum;
}

const SC_Vector& Gfx_Camera::GetForward() const
{
	return mForward;
}

const SC_Vector& Gfx_Camera::GetUp() const
{
	return mUp;
}

const SC_Vector& Gfx_Camera::GetRight() const
{
	return mRight;
}

const SC_Vector2& Gfx_Camera::GetSize() const
{
	return mSize;
}

float Gfx_Camera::GetFov() const
{
	return mFov;
}

float Gfx_Camera::GetNear() const
{
	return mNear;
}

float Gfx_Camera::GetFar() const
{
	return mFar;
}

float Gfx_Camera::GetAspectRatio() const
{
	return mAspectRatio;
}

SC_Vector Gfx_Camera::GetPosition() const
{
	return mTransform.GetPosition();
}

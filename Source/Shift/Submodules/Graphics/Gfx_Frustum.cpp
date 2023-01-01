//ProjectFilter(View)
#include "Graphics_Precompiled.h"
#include "Gfx_Frustum.h"

Gfx_Frustum::Gfx_Frustum()
{
}

Gfx_Frustum::~Gfx_Frustum()
{
}

void Gfx_Frustum::Update(const SC_Matrix& aViewProj)
{
	mPlanes[FrustumPlane_Right].mNormal.x = aViewProj.mData[3] - aViewProj.mData[0];
	mPlanes[FrustumPlane_Right].mNormal.y = aViewProj.mData[7] - aViewProj.mData[4];
	mPlanes[FrustumPlane_Right].mNormal.z = aViewProj.mData[11] - aViewProj.mData[8];
	mPlanes[FrustumPlane_Right].mDistance = aViewProj.mData[15] - aViewProj.mData[12];
	mPlanes[FrustumPlane_Right].Normalize();

	mPlanes[FrustumPlane_Left].mNormal.x = aViewProj.mData[3] + aViewProj.mData[0];
	mPlanes[FrustumPlane_Left].mNormal.y = aViewProj.mData[7] + aViewProj.mData[4];
	mPlanes[FrustumPlane_Left].mNormal.z = aViewProj.mData[11] + aViewProj.mData[8];
	mPlanes[FrustumPlane_Left].mDistance = aViewProj.mData[15] + aViewProj.mData[12];
	mPlanes[FrustumPlane_Left].Normalize();

	mPlanes[FrustumPlane_Top].mNormal.x = aViewProj.mData[3] - aViewProj.mData[1];
	mPlanes[FrustumPlane_Top].mNormal.y = aViewProj.mData[7] - aViewProj.mData[5];
	mPlanes[FrustumPlane_Top].mNormal.z = aViewProj.mData[11] - aViewProj.mData[9];
	mPlanes[FrustumPlane_Top].mDistance = aViewProj.mData[15] - aViewProj.mData[13];
	mPlanes[FrustumPlane_Top].Normalize();

	mPlanes[FrustumPlane_Bottom].mNormal.x = aViewProj.mData[3] + aViewProj.mData[1];
	mPlanes[FrustumPlane_Bottom].mNormal.y = aViewProj.mData[7] + aViewProj.mData[5];
	mPlanes[FrustumPlane_Bottom].mNormal.z = aViewProj.mData[11] + aViewProj.mData[9];
	mPlanes[FrustumPlane_Bottom].mDistance = aViewProj.mData[15] + aViewProj.mData[13];
	mPlanes[FrustumPlane_Bottom].Normalize();

	mPlanes[FrustumPlane_Near].mNormal.x = aViewProj.mData[3] - aViewProj.mData[2];
	mPlanes[FrustumPlane_Near].mNormal.y = aViewProj.mData[7] - aViewProj.mData[6];
	mPlanes[FrustumPlane_Near].mNormal.z = aViewProj.mData[11] - aViewProj.mData[10];
	mPlanes[FrustumPlane_Near].mDistance = aViewProj.mData[15] - aViewProj.mData[14];
	mPlanes[FrustumPlane_Near].Normalize();

	mPlanes[FrustumPlane_Far].mNormal.x = aViewProj.mData[2];
	mPlanes[FrustumPlane_Far].mNormal.y = aViewProj.mData[6];
	mPlanes[FrustumPlane_Far].mNormal.z = aViewProj.mData[10];
	mPlanes[FrustumPlane_Far].mDistance = aViewProj.mData[14];
	mPlanes[FrustumPlane_Far].Normalize();
}

bool Gfx_Frustum::Intersects(const SC_AABB& aBoundingBox) const
{
	bool aResult = true;
	for (uint32 planeIdx = 0; planeIdx < FrustumPlanes_COUNT; ++planeIdx)
	{
		SC_Vector AxisVert;
		if (mPlanes[planeIdx].mNormal.x < 0.0f)
			AxisVert.x = aBoundingBox.mMin.x;
		else
			AxisVert.x = aBoundingBox.mMax.x;

		if (mPlanes[planeIdx].mNormal.y < 0.0f)
			AxisVert.y = aBoundingBox.mMin.y;
		else
			AxisVert.y = aBoundingBox.mMax.y;

		if (mPlanes[planeIdx].mNormal.z < 0.0f)
			AxisVert.z = aBoundingBox.mMin.z;
		else
			AxisVert.z = aBoundingBox.mMax.z;

		if (mPlanes[planeIdx].DistanceToPlane(AxisVert) < 0.0f)
		{
			aResult = false;
			break;
		}
	}

	return aResult;
}

bool Gfx_Frustum::Intersects(const SC_Sphere& aBoundingSphere) const
{
	float minDist = 0.0f;
	for (uint32 planeIdx = 0; planeIdx < FrustumPlanes_COUNT; ++planeIdx)
	{
		float dist = mPlanes[planeIdx].DistanceToPlane(aBoundingSphere.mCenter);
		minDist = SC_Min(minDist, dist);
	}

	return minDist > (-aBoundingSphere.mRadius);
}

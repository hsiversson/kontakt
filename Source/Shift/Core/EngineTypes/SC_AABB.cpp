//ProjectFilter(Geometry)
#include "EngineTypes_Precompiled.h"
#include "SC_AABB.h"

SC_AABB::SC_AABB()
{

}

SC_AABB::SC_AABB(const SC_Vector& aMin, const SC_Vector& aMax)
	: mMin(aMin)
	, mMax(aMax)
{
}

SC_AABB::~SC_AABB()
{

}



void SC_AABB::FromPoints(const SC_Vector* aPoints, uint32 aCount)
{
	SC_ASSERT(aCount > 0);
	mMin = aPoints[0];
	mMax = aPoints[0];
	for (uint32 i = 1; i < aCount; ++i)
	{
		mMin.x = SC_Min(mMin.x, aPoints[i].x);
		mMin.y = SC_Min(mMin.y, aPoints[i].y);
		mMin.z = SC_Min(mMin.z, aPoints[i].z);
		mMax.x = SC_Max(mMax.x, aPoints[i].x);
		mMax.y = SC_Max(mMax.y, aPoints[i].y);
		mMax.z = SC_Max(mMax.z, aPoints[i].z);
	}
}

SC_Vector SC_AABB::GetCenter() const
{
	return (mMax + mMin) * 0.5f;
}

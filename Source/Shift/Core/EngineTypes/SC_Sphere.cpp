//ProjectFilter(Geometry)
#include "EngineTypes_Precompiled.h"
#include "SC_Sphere.h"
#include "SC_AABB.h"

SC_Sphere::SC_Sphere()
	: mCenter(0.0f)
	, mRadius(1.0f)
{

}

SC_Sphere::SC_Sphere(const SC_Vector& aCenter, float aRadius)
	: mCenter(aCenter)
	, mRadius(aRadius)
{

}

SC_Sphere::SC_Sphere(const SC_Sphere& aOther)
	: mCenter(aOther.mCenter)
	, mRadius(aOther.mRadius)
{
}

SC_Sphere::SC_Sphere(const SC_AABB& aAABB)
{
	const SC_Vector& point0 = aAABB.mMin;
	const SC_Vector& point1 = aAABB.mMax;
	mCenter = (point0 + point1) * 0.5f;
	mRadius = (point1 - point0).Length() * 0.5f;
}

bool SC_Sphere::IsInside(const SC_Vector& aPoint) const
{
	if ((mCenter - aPoint).Length2() < (mRadius * mRadius))
		return true;

	return false;
}

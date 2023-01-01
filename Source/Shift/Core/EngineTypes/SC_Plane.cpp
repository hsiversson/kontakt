//ProjectFilter(Geometry)
#include "EngineTypes_Precompiled.h"
#include "SC_Plane.h"

SC_Plane::SC_Plane()
{

}

SC_Plane::SC_Plane(const SC_Vector& aNormal, float aDistance)
	: mNormal(aNormal)
	, mDistance(aDistance)
{

}

SC_Plane::~SC_Plane()
{

}

void SC_Plane::Normalize()
{
	SC_Vector4 v(mNormal, mDistance);
	v.Normalize();

	mNormal = v.XYZ();
	mDistance = v.w;
}

float SC_Plane::DistanceToPlane(const SC_Vector& aPoint) const
{
	return mNormal.Dot(aPoint) + mDistance;
}

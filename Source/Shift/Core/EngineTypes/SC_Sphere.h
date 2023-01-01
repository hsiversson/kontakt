//ProjectFilter(Geometry)
#pragma once

class SC_AABB;
class SC_Sphere
{
public:
	SC_Sphere();
	SC_Sphere(const SC_Vector& aCenter, float aRadius);
	SC_Sphere(const SC_Sphere& aOther);
	SC_Sphere(const SC_AABB& aAABB);
	~SC_Sphere() {}

	bool IsInside(const SC_Vector& aPoint) const;

	SC_Vector mCenter;
	float mRadius;
};
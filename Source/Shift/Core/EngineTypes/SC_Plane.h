//ProjectFilter(Geometry)
#pragma once

class SC_Plane
{
public:
	SC_Plane();
	SC_Plane(const SC_Vector& aNormal, float aDistance);
	~SC_Plane();

	void Normalize();
	float DistanceToPlane(const SC_Vector& aPoint) const;

	SC_Vector mNormal;
	float mDistance;
};


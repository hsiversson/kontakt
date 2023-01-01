//ProjectFilter(Geometry)
#pragma once

class SC_AABB
{
public:
	SC_AABB();
	SC_AABB(const SC_Vector& aMin, const SC_Vector& aMax);
	~SC_AABB();

	void FromPoints(const SC_Vector* aPoints, uint32 aCount);
	SC_Vector GetCenter() const;

	SC_Vector mMin;
	SC_Vector mMax;
};
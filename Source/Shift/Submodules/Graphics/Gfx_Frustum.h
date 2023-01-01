//ProjectFilter(View)
#pragma once

class Gfx_Frustum
{
	enum FrustumPlanes
	{
		FrustumPlane_Near = 0,
		FrustumPlane_Right,
		FrustumPlane_Left,
		FrustumPlane_Bottom,
		FrustumPlane_Top,
		FrustumPlane_Far,
		FrustumPlanes_COUNT,
	};

public:
	Gfx_Frustum();
	~Gfx_Frustum();

	void Update(const SC_Matrix& aViewProj);

	bool Intersects(const SC_AABB& aBoundingBox) const;
	bool Intersects(const SC_Sphere& aBoundingSphere) const;

private:
	SC_Plane mPlanes[FrustumPlanes_COUNT];
};


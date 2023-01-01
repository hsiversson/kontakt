//ProjectFilter(Mesh)
#pragma once
#include "Gfx_Mesh.h"

class Gfx_MeshInstance : public SC_ReferenceCounted
{
public:
	Gfx_MeshInstance(Gfx_Mesh* aMesh);
	~Gfx_MeshInstance();

	Gfx_Mesh* GetMesh() const;

	const SC_AABB& GetBoundingBox() const;
private:
	SC_AABB mBoundingBox;

	SC_Ref<Gfx_Mesh> mMesh;
};


//ProjectFilter(Mesh)
#pragma once
#include "Gfx_Mesh.h"
#include "Gfx_MaterialInstance.h"

class Gfx_MeshInstance : public SC_ReferenceCounted
{
public:
	Gfx_MeshInstance(Gfx_Mesh* aMesh);
	~Gfx_MeshInstance();

	Gfx_Mesh* GetMesh() const;
	Gfx_MaterialInstance* GetMaterialInstance() const;

	const SC_AABB& GetBoundingBox() const;
private:
	SC_AABB mBoundingBox;

	SC_Ref<Gfx_Mesh> mMesh;
	SC_Ref<Gfx_MaterialInstance> mMaterialInstance;
};


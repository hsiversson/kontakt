//ProjectFilter(Mesh)
#include "Graphics_Precompiled.h"
#include "Gfx_MeshInstance.h"

Gfx_MeshInstance::Gfx_MeshInstance(Gfx_Mesh* aMesh)
	: mMesh(aMesh)
{

}

Gfx_MeshInstance::~Gfx_MeshInstance()
{

}

Gfx_Mesh* Gfx_MeshInstance::GetMesh() const
{
	return mMesh;
}

Gfx_MaterialInstance* Gfx_MeshInstance::GetMaterialInstance() const
{
	return mMaterialInstance;
}

const SC_AABB& Gfx_MeshInstance::GetBoundingBox() const
{
	return mBoundingBox;
}

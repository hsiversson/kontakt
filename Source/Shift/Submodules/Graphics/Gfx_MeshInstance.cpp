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

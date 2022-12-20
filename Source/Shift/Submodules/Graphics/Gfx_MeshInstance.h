//ProjectFilter(Mesh)
#pragma once
#include "Gfx_Mesh.h"

class Gfx_MeshInstance : public SC_ReferenceCounted
{
public:
	Gfx_MeshInstance(Gfx_Mesh* aMesh);
	~Gfx_MeshInstance();

	Gfx_Mesh* GetMesh() const;

private:
	SC_Ref<Gfx_Mesh> mMesh;
};


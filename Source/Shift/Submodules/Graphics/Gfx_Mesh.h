//ProjectFilter(Mesh)
#pragma once
#include "Gfx_Meshlet.h"

struct Gfx_MeshCreateProperties
{

};

class Gfx_Mesh : public SC_ReferenceCounted
{
public:
	Gfx_Mesh();
	~Gfx_Mesh();

private:
	// Meshlets
	// Vertices


	SC_Ref<SR_BufferResource> mMeshletBuffer;
	SC_Ref<SR_BufferResource> mVertexBuffer;
};


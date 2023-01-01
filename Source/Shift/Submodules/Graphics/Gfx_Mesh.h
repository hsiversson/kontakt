//ProjectFilter(Mesh)
#pragma once
#include "Gfx_Meshlet.h"

struct Gfx_MeshCreateProperties
{
	Gfx_MeshCreateProperties() : mVertexIndicesStride(0), mUseMeshlets(false) {}

	std::string mSourceFile;

	SC_AABB mBoundingBox;

	SR_VertexLayout mVertexLayout;
	SC_Array<uint8> mVertexData;

	SC_Array<Gfx_Meshlet> mMeshlets;
	SC_Array<Gfx_PackedPrimitiveTriangle> mPrimitiveIndices;
	SC_Array<uint8> mVertexIndices;
	uint32 mVertexIndicesStride;

	bool mUseMeshlets;
};


struct SGfx_MeshletBuffers
{
	SC_Ref<SR_Buffer> mVertexBuffer;
	SC_Ref<SR_Buffer> mMeshletBuffer;
	SC_Ref<SR_Buffer> mVertexIndexBuffer;
	SC_Ref<SR_Buffer> mPrimitiveIndexBuffer;
};

class Gfx_Mesh : public SC_ReferenceCounted
{
public:
	Gfx_Mesh();
	~Gfx_Mesh();

	const SR_VertexLayout& GetVertexLayout() const;

	SR_BufferResource* GetVertexBufferResource() const;
	SR_Buffer* GetVertexBuffer() const;
	SR_BufferResource* GetIndexBufferResource() const;
	SR_Buffer* GetIndexBuffer() const;

#if SR_ENABLE_MESH_SHADERS
	const SGfx_MeshletBuffers& GetMeshletBuffers() const;
	bool IsUsingMeshlets() const;
#endif

	const SC_AABB& GetBoundingBox() const;

private:
	bool Init(const Gfx_MeshCreateProperties& aCreateProperties);
	bool InitDefault(const Gfx_MeshCreateProperties& aCreateProperties);
#if SR_ENABLE_MESH_SHADERS
	bool InitMeshlet(const Gfx_MeshCreateProperties& aCreateProperties);
#endif
private:
	// Meshlets
	// Vertices

	SC_Ref<SR_BufferResource> mIndexBufferResource;
	SC_Ref<SR_Buffer> mIndexBuffer;

	SC_Ref<SR_BufferResource> mVertexBufferResource;
	SC_Ref<SR_Buffer> mVertexBuffer;

	SGfx_MeshletBuffers mMeshletBuffers;
	SR_VertexLayout mVertexLayout;
	SC_AABB mBoundingBox;

	bool mUseMeshlets;
};


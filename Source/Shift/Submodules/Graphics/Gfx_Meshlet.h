//ProjectFilter(Mesh)
#pragma once

static uint32 SC_MaxMeshletVertices = 64;
static uint32 SC_MaxMeshletPrimitives = 64;

struct Gfx_Meshlet
{
	uint32 mVertexCount;
	uint32 mVertexOffset;
	uint32 mPrimitiveCount;
	uint32 mPrimitiveOffset;
};

struct Gfx_PackedPrimitiveTriangle
{
	Gfx_PackedPrimitiveTriangle() : mIndex0(SC_UINT32_MAX), mIndex1(SC_UINT32_MAX), mIndex2(SC_UINT32_MAX), __pad(0) {}
	Gfx_PackedPrimitiveTriangle(uint32 aIndex0, uint32 aIndex1, uint32 aIndex2) : mIndex0(aIndex0), mIndex1(aIndex1), mIndex2(aIndex2), __pad(0) {}

	SC_Vector3ui Unpack() const
	{
		return SC_Vector3ui(mIndex0 & 0x3FF, mIndex1 & 0x3FF, mIndex2 & 0x3FF);
	}

	uint32 mIndex0 : 10;
	uint32 mIndex1 : 10;
	uint32 mIndex2 : 10;
private:
	uint32 __pad : 2;
};

bool Gfx_FlattenMeshletPrimitivesToIndexBuffer(
	const SC_Array<Gfx_Meshlet>& aMeshlets,
	const SC_Array<Gfx_PackedPrimitiveTriangle>& aPrimitives,
	const SC_Array<uint8>& aUniqueVertexIndices,
	const uint32 aVertexIndicesStride,
	SC_Array<uint8>& aOutIndexData,
	uint32& aOutIndexStride);

bool Gfx_GenerateMeshlets(
	uint32 aMaxVertices,
	uint32 aMaxPrimitives,
	const uint8* aVertexData,
	const SR_VertexLayout& aVertexLayout,
	const uint32 aNumVertices,
	const uint8* aIndexData,
	bool aUse16BitIndices,
	const uint32 aNumIndices,
	SC_Array<Gfx_Meshlet>& aOutMeshlets,
	SC_Array<Gfx_PackedPrimitiveTriangle>& aOutPrimitives,
	SC_Array<uint8>& aOutVertexIndices);
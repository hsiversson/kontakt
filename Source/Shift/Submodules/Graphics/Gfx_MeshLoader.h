//ProjectFilter(Mesh)
#pragma once
#include "Gfx_Mesh.h"

class Gfx_MeshLoader
{
public:
	static constexpr const char* gFileExtension = "smf";

	static bool Save(const std::string& aFilename, const Gfx_MeshCreateProperties& aCreateProperties);
	static bool Load(const std::string& aFilename, Gfx_MeshCreateProperties& aOutCreateProperties);
	
private:
	struct FileTOC
	{
		uint32 mSMFMagic;
		uint32 mVersion;
		bool mHasMeshletData;
	};
	struct MeshTOC
	{
		SC_Vector mMinBounds;
		SC_Vector mMaxBounds;
		uint32 mNumVertices;
		uint32 mNumMeshlets;
		uint32 mMeshletStride;
		uint32 mNumPrimitiveIndices;
		uint32 mPrimitiveIndicesStride;
		uint32 mNumVertexIndices;
		uint32 mVertexIndicesStride;
		uint32 mNumVertexAttributes;
	};
};


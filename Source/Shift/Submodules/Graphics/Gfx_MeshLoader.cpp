//ProjectFilter(Mesh)
#include "Graphics_Precompiled.h"
#include "Gfx_MeshLoader.h"

#include <fstream>

static constexpr uint32 gSMFMagic = 0x20464d53; // "SMF "
static constexpr uint32 gVersion = 1;

bool Gfx_MeshLoader::Save(const std::string& aFilename, const Gfx_MeshCreateProperties& aCreateProperties)
{
	std::ofstream outStream(aFilename, std::ofstream::out | std::ofstream::binary);

	if (!outStream.is_open())
		return false;

	FileTOC fileTOC;
	fileTOC.mSMFMagic = gSMFMagic;
	fileTOC.mVersion = gVersion;
	fileTOC.mHasMeshletData = aCreateProperties.mUseMeshlets;

	outStream.write(reinterpret_cast<char*>(&fileTOC), sizeof(FileTOC));

	const uint32 vertexStrideSize = aCreateProperties.mVertexLayout.GetVertexStrideSize();

	MeshTOC meshTOC;
	meshTOC.mMinBounds = aCreateProperties.mBoundingBox.mMin;
	meshTOC.mMaxBounds = aCreateProperties.mBoundingBox.mMax;
	meshTOC.mNumVertices = aCreateProperties.mVertexData.Count() / vertexStrideSize;
	meshTOC.mNumMeshlets = aCreateProperties.mMeshlets.Count();
	meshTOC.mMeshletStride = sizeof(Gfx_Meshlet);
	meshTOC.mNumPrimitiveIndices = aCreateProperties.mPrimitiveIndices.Count();
	meshTOC.mPrimitiveIndicesStride = sizeof(Gfx_PackedPrimitiveTriangle);
	meshTOC.mVertexIndicesStride = aCreateProperties.mVertexIndicesStride;
	meshTOC.mNumVertexIndices = aCreateProperties.mVertexIndices.Count() / meshTOC.mVertexIndicesStride;
	meshTOC.mNumVertexAttributes = aCreateProperties.mVertexLayout.mAttributes.Count();

	outStream.write(reinterpret_cast<const char*>(&meshTOC), sizeof(MeshTOC));
	outStream.write(reinterpret_cast<const char*>(aCreateProperties.mVertexLayout.mAttributes.GetBuffer()), aCreateProperties.mVertexLayout.mAttributes.GetByteSize());
	outStream.write(reinterpret_cast<const char*>(aCreateProperties.mVertexData.GetBuffer()), vertexStrideSize * meshTOC.mNumVertices);
	outStream.write(reinterpret_cast<const char*>(aCreateProperties.mMeshlets.GetBuffer()), meshTOC.mMeshletStride * meshTOC.mNumMeshlets);
	outStream.write(reinterpret_cast<const char*>(aCreateProperties.mPrimitiveIndices.GetBuffer()), meshTOC.mPrimitiveIndicesStride * meshTOC.mNumPrimitiveIndices);
	outStream.write(reinterpret_cast<const char*>(aCreateProperties.mVertexIndices.GetBuffer()), meshTOC.mVertexIndicesStride * meshTOC.mNumVertexIndices);

	return true;
}

bool Gfx_MeshLoader::Load(const std::string& aFilename, Gfx_MeshCreateProperties& aOutCreateProperties)
{
	std::ifstream inStream(aFilename, std::ifstream::in | std::ifstream::binary);
	if (inStream.is_open())
	{
		FileTOC fileTOC;
		inStream.read(reinterpret_cast<char*>(&fileTOC), sizeof(FileTOC));

		if (fileTOC.mSMFMagic != gSMFMagic)
		{
			SC_ERROR("This file is not an SMF file.");
			return false;
		}

		if (fileTOC.mVersion != gVersion)
		{
			SC_ASSERT(false, "Invalid SMF version. [got: {}, expected: {}]", fileTOC.mVersion, gVersion);
			return false;
		}

		MeshTOC meshTOC;
		inStream.read(reinterpret_cast<char*>(&meshTOC), sizeof(MeshTOC));

		aOutCreateProperties.mUseMeshlets = fileTOC.mHasMeshletData;
		aOutCreateProperties.mBoundingBox.mMin = meshTOC.mMinBounds;
		aOutCreateProperties.mBoundingBox.mMax = meshTOC.mMaxBounds;
		aOutCreateProperties.mVertexIndicesStride = meshTOC.mVertexIndicesStride;

		aOutCreateProperties.mVertexLayout.mAttributes.Respace(meshTOC.mNumVertexAttributes);
		inStream.read(reinterpret_cast<char*>(aOutCreateProperties.mVertexLayout.mAttributes.GetBuffer()), aOutCreateProperties.mVertexLayout.mAttributes.GetByteSize());

		const uint32 vertexDataSize = meshTOC.mNumVertices * aOutCreateProperties.mVertexLayout.GetVertexStrideSize();
		const uint32 meshletDataSize = meshTOC.mNumMeshlets * meshTOC.mMeshletStride;
		const uint32 primitiveIndicesDataSize = meshTOC.mNumPrimitiveIndices * meshTOC.mPrimitiveIndicesStride;
		const uint32 vertexIndicesDataSize = meshTOC.mNumVertexIndices * meshTOC.mVertexIndicesStride;

		aOutCreateProperties.mVertexData.Respace(vertexDataSize);
		aOutCreateProperties.mMeshlets.Respace(meshTOC.mNumMeshlets);
		aOutCreateProperties.mPrimitiveIndices.Respace(meshTOC.mNumPrimitiveIndices);
		aOutCreateProperties.mVertexIndices.Respace(vertexIndicesDataSize);

		inStream.read(reinterpret_cast<char*>(aOutCreateProperties.mVertexData.GetBuffer()), vertexDataSize);
		inStream.read(reinterpret_cast<char*>(aOutCreateProperties.mMeshlets.GetBuffer()), meshletDataSize);
		inStream.read(reinterpret_cast<char*>(aOutCreateProperties.mPrimitiveIndices.GetBuffer()), primitiveIndicesDataSize);
		inStream.read(reinterpret_cast<char*>(aOutCreateProperties.mVertexIndices.GetBuffer()), vertexIndicesDataSize);
	}
	else
		return false;

	aOutCreateProperties.mSourceFile = aFilename;
	return true;
}
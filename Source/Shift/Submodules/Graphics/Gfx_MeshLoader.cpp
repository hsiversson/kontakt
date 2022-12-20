//ProjectFilter(Mesh)
#include "Graphics_Precompiled.h"
#include "Gfx_MeshLoader.h"

#include <fstream>

bool Gfx_MeshLoader::Save(const std::string& aFileName, const Gfx_MeshCreateProperties& aCreateProperties)
{
	std::ofstream outStream(aFileName, std::ofstream::out | std::ofstream::binary);

	if (!outStream.is_open())
		return false;

	FileTOC fileTOC;
	fileTOC.mVersion = gVersion;
	fileTOC.mHasMeshletData = aCreateProperties.mIsMeshletData;

	outStream.write(reinterpret_cast<char*>(&fileTOC), sizeof(FileTOC));

	const uint32 vertexStrideSize = aCreateProperties.mVertexLayout.GetVertexStrideSize();

	MeshTOC meshTOC;
	meshTOC.mMinBounds = aCreateProperties.mMinBounds;
	meshTOC.mMaxBounds = aCreateProperties.mMaxBounds;
	meshTOC.mNumVertices = aCreateProperties.mVertexData.Count() / vertexStrideSize;
	meshTOC.mNumMeshlets = aCreateProperties.mMeshlets.Count();
	meshTOC.mMeshletStride = sizeof(Gfx_Meshlet);
	meshTOC.mNumPrimitiveIndices = aCreateProperties.mPrimitiveIndices.Count();
	meshTOC.mPrimitiveIndicesStride = sizeof(SGfx_PackedPrimitiveTriangle);
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

bool Gfx_MeshLoader::Load(const std::string& aFilePath, Gfx_MeshCreateProperties& aOutCreateProperties)
{
	std::ifstream inStream(aFilePath, std::ifstream::in | std::ifstream::binary);
	if (inStream.is_open())
	{
		FileTOC fileTOC;
		inStream.read(reinterpret_cast<char*>(&fileTOC), sizeof(FileTOC));

		MeshTOC meshTOC;
		inStream.read(reinterpret_cast<char*>(&meshTOC), sizeof(MeshTOC));

		aOutCreateProperties.mIsMeshletData = fileTOC.mHasMeshletData;
		aOutCreateProperties.mMinBounds = meshTOC.mMinBounds;
		aOutCreateProperties.mMaxBounds = meshTOC.mMaxBounds;
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

	aOutCreateProperties.mSourceFile = aFilePath;
	return true;
}
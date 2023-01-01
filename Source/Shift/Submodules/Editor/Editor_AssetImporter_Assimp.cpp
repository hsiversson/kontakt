#include "Editor_Precompiled.h"
#include "Editor_AssetImporter_Assimp.h"

#include "Gfx_Mesh.h"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

class Editor_AssimpMaterial
{
public:
	Editor_AssimpMaterial() : mTwoSided(false) {}
	~Editor_AssimpMaterial() {}

	bool Init(aiMaterial* aImportedMaterial)
	{
		aiString path;
		for (uint32 i = 0; i < AI_TEXTURE_TYPE_MAX; ++i)
		{
			const aiTextureType texType = (aiTextureType)i;
			aiReturn texFound = aImportedMaterial->GetTexture(texType, 0, &path);

			if (texFound == AI_SUCCESS)
				mTextures.Add(path.data);
		}

		{
			int twoSided = 0;
			aImportedMaterial->Get(AI_MATKEY_TWOSIDED, twoSided);
			mTwoSided = (bool)twoSided;
		}

		return true;
	}

private:
	SC_Array<std::string> mTextures;
	bool mTwoSided;
};

class Editor_AssimpMesh
{
public:
	Editor_AssimpMesh() : mMaterialIndex(0) {}
	~Editor_AssimpMesh() {}

	bool Init(aiMesh* aImportedMesh)
	{
		TempMeshData meshData;

		// Setup Vertex Layout
		mMeshCreateProperties.mVertexLayout.SetAttribute(SR_VertexAttribute::Position, SR_Format::RGB32_FLOAT);

		if (aImportedMesh->HasNormals())
			mMeshCreateProperties.mVertexLayout.SetAttribute(SR_VertexAttribute::Normal, SR_Format::RGB32_FLOAT);

		if (aImportedMesh->HasTangentsAndBitangents())
		{
			mMeshCreateProperties.mVertexLayout.SetAttribute(SR_VertexAttribute::Tangent, SR_Format::RGB32_FLOAT);
			mMeshCreateProperties.mVertexLayout.SetAttribute(SR_VertexAttribute::Bitangent, SR_Format::RGB32_FLOAT);
		}

		if (aImportedMesh->HasTextureCoords(0))
			mMeshCreateProperties.mVertexLayout.SetAttribute(SR_VertexAttribute::UV, SR_Format::RG32_FLOAT, 0);
		if (aImportedMesh->HasTextureCoords(1))
			mMeshCreateProperties.mVertexLayout.SetAttribute(SR_VertexAttribute::UV, SR_Format::RG32_FLOAT, 1);

		if (aImportedMesh->HasVertexColors(0))
			mMeshCreateProperties.mVertexLayout.SetAttribute(SR_VertexAttribute::Color, SR_Format::RGBA32_FLOAT, 0);
		if (aImportedMesh->HasVertexColors(1))
			mMeshCreateProperties.mVertexLayout.SetAttribute(SR_VertexAttribute::Color, SR_Format::RGBA32_FLOAT, 1);

		// Extract Vertices
		{
			const uint32 vertexStrideSize = mMeshCreateProperties.mVertexLayout.GetVertexStrideSize();
			const uint32 vertexDataArraySize = aImportedMesh->mNumVertices * vertexStrideSize;
			mMeshCreateProperties.mVertexData.Respace(vertexDataArraySize);

			uint32 currentDataArrayPos = 0;
			mMeshCreateProperties.mBoundingBox.mMin = SC_Vector(SC_FLT_MAX);
			mMeshCreateProperties.mBoundingBox.mMax = SC_Vector(SC_FLT_LOWEST);
			const SC_Array<SR_VertexAttributeData>& vertexAttributes = mMeshCreateProperties.mVertexLayout.mAttributes;
			for (uint32 i = 0; i < aImportedMesh->mNumVertices; ++i)
			{
				for (const SR_VertexAttributeData& vAttribute : vertexAttributes)
				{
					if (vAttribute.mAttributeId == SR_VertexAttribute::Position)
					{
						const aiVector3D& pos = aImportedMesh->mVertices[i];
						SC_Vector vPosition = SC_Vector(pos.x, pos.y, pos.z);
						SC_Memcpy(&mMeshCreateProperties.mVertexData[currentDataArrayPos], &vPosition, sizeof(SC_Vector));
						currentDataArrayPos += sizeof(SC_Vector);

						mMeshCreateProperties.mBoundingBox.mMin.x = SC_Min(vPosition.x, mMeshCreateProperties.mBoundingBox.mMin.x);
						mMeshCreateProperties.mBoundingBox.mMin.y = SC_Min(vPosition.y, mMeshCreateProperties.mBoundingBox.mMin.y);
						mMeshCreateProperties.mBoundingBox.mMin.z = SC_Min(vPosition.z, mMeshCreateProperties.mBoundingBox.mMin.z);
						mMeshCreateProperties.mBoundingBox.mMax.x = SC_Max(vPosition.x, mMeshCreateProperties.mBoundingBox.mMax.x);
						mMeshCreateProperties.mBoundingBox.mMax.y = SC_Max(vPosition.y, mMeshCreateProperties.mBoundingBox.mMax.y);
						mMeshCreateProperties.mBoundingBox.mMax.z = SC_Max(vPosition.z, mMeshCreateProperties.mBoundingBox.mMax.z);
					}
					else if (vAttribute.mAttributeId == SR_VertexAttribute::Normal)
					{
						const aiVector3D& normal = aImportedMesh->mNormals[i];
						SC_Vector vNormal = SC_Vector(normal.x, normal.y, normal.z);
						vNormal.Normalize();
						SC_Memcpy(&mMeshCreateProperties.mVertexData[currentDataArrayPos], &vNormal, sizeof(SC_Vector));
						currentDataArrayPos += sizeof(SC_Vector);
					}
					else if (vAttribute.mAttributeId == SR_VertexAttribute::Tangent)
					{
						const aiVector3D& tangent = aImportedMesh->mNormals[i];
						SC_Vector vTangent = SC_Vector(tangent.x, tangent.y, tangent.z);
						vTangent.Normalize();
						SC_Memcpy(&mMeshCreateProperties.mVertexData[currentDataArrayPos], &vTangent, sizeof(SC_Vector));
						currentDataArrayPos += sizeof(SC_Vector);
					}
					else if (vAttribute.mAttributeId == SR_VertexAttribute::Bitangent)
					{
						const aiVector3D& bitangent = aImportedMesh->mNormals[i];
						SC_Vector vBitangent = SC_Vector(bitangent.x, bitangent.y, bitangent.z);
						vBitangent.Normalize();
						SC_Memcpy(&mMeshCreateProperties.mVertexData[currentDataArrayPos], &vBitangent, sizeof(SC_Vector));
						currentDataArrayPos += sizeof(SC_Vector);
					}
					else if (vAttribute.mAttributeId == SR_VertexAttribute::UV)
					{
						const aiVector3D& uvw = aImportedMesh->mTextureCoords[vAttribute.mAttributeIndex][i];
						SC_Vector2 vUV = SC_Vector2(uvw.x, uvw.y);
						SC_Memcpy(&mMeshCreateProperties.mVertexData[currentDataArrayPos], &vUV, sizeof(SC_Vector2));
						currentDataArrayPos += sizeof(SC_Vector2);
					}
					else if (vAttribute.mAttributeId == SR_VertexAttribute::Color)
					{
						const aiColor4D& color = aImportedMesh->mColors[vAttribute.mAttributeIndex][i];
						SC_Vector4 vColor = SC_Vector4(color.r, color.g, color.b, color.a);
						SC_Memcpy(&mMeshCreateProperties.mVertexData[currentDataArrayPos], &vColor, sizeof(SC_Vector4));
						currentDataArrayPos += sizeof(SC_Vector4);
					}
				}
			}
		}

		// Extract Indices
		{
			static constexpr uint32 gMaxNumFaceIndices = 3; // For triangle

			const uint32 numIndices = aImportedMesh->mNumFaces * gMaxNumFaceIndices;
			const bool use16BitIndices = numIndices < SC_UINT16_MAX;
			meshData.mIndexStride = (use16BitIndices) ? sizeof(uint16) : sizeof(uint32);
			meshData.mIndexData.Respace(numIndices * meshData.mIndexStride);

			const uint32 faceStride = meshData.mIndexStride * gMaxNumFaceIndices;

			uint32 currentDataArrayPos = 0;
			for (uint32 faceIdx = 0; faceIdx < aImportedMesh->mNumFaces; ++faceIdx)
			{
				const aiFace& face = aImportedMesh->mFaces[faceIdx];
				SC_ASSERT(face.mNumIndices == gMaxNumFaceIndices && "Mesh isn't triangulated.");

				if (use16BitIndices)
				{
					uint16 indices[gMaxNumFaceIndices] = { (uint16)face.mIndices[0], (uint16)face.mIndices[1], (uint16)face.mIndices[2] };
					SC_Memcpy(&meshData.mIndexData[currentDataArrayPos], &indices, faceStride);
					currentDataArrayPos += faceStride;
				}
				else
				{
					uint32 indices[gMaxNumFaceIndices] = { (uint32)face.mIndices[0], (uint32)face.mIndices[1], (uint32)face.mIndices[2] };
					SC_Memcpy(&meshData.mIndexData[currentDataArrayPos], &indices, faceStride);
					currentDataArrayPos += faceStride;
				}
			}
		}

		mMaterialIndex = aImportedMesh->mMaterialIndex;

		if (!GenerateMeshletData(meshData))
			return false;

		return true;
	}

private:
	struct TempMeshData
	{
		SC_Array<uint8> mIndexData;
		uint32 mIndexStride;
	};

	bool GenerateMeshletData(const TempMeshData& aMeshData)
	{
		const uint32 numVertices = mMeshCreateProperties.mVertexData.Count() / mMeshCreateProperties.mVertexLayout.GetVertexStrideSize();
		const uint32 numIndices = aMeshData.mIndexData.Count() / aMeshData.mIndexStride;

		mMeshCreateProperties.mVertexIndicesStride = aMeshData.mIndexStride;

		return Gfx_GenerateMeshlets(
			SC_MaxMeshletVertices,
			SC_MaxMeshletPrimitives,
			mMeshCreateProperties.mVertexData.GetBuffer(),
			mMeshCreateProperties.mVertexLayout,
			numVertices,
			aMeshData.mIndexData.GetBuffer(),
			(aMeshData.mIndexStride == sizeof(uint16)) ? true : false,
			numIndices,
			mMeshCreateProperties.mMeshlets,
			mMeshCreateProperties.mPrimitiveIndices,
			mMeshCreateProperties.mVertexIndices);
	}

	Gfx_MeshCreateProperties mMeshCreateProperties;
	uint32 mMaterialIndex;
};

class Editor_AssimpEntity
{
public:
	Editor_AssimpEntity() {}
	~Editor_AssimpEntity() {}

	bool Init(aiNode* aNode)
	{
		aiVector3D aiPosition;
		aiVector3D aiRotation;
		aiVector3D aiScale;
		aNode->mTransformation.Decompose(aiScale, aiRotation, aiPosition);

		mPosition = SC_Vector(aiPosition.x, aiPosition.y, aiPosition.z);
		mScale = SC_Vector(aiScale.x, aiScale.y, aiScale.z);
		mRotation = SC_Vector(aiRotation.x, aiRotation.y, aiRotation.z);

		mName = aNode->mName.C_Str();

		const uint32 numMeshes = aNode->mNumMeshes;
		mMeshReferences.Respace(numMeshes);
		for (uint32 i = 0; i < numMeshes; ++i)
			mMeshReferences[i] = aNode->mMeshes[i];

		const uint32 numChildren = aNode->mNumChildren;
		mChildren.Respace(numChildren);
		for (uint32 i = 0; i < numChildren; ++i)
		{
			if (!mChildren[i].Init(aNode->mChildren[i]))
				return false;
		}

		return true;
	}

private:
	SC_Array<Editor_AssimpEntity> mChildren;
	SC_Array<uint32> mMeshReferences;

	SC_Vector mPosition;	// Relative to parent
	SC_Vector mRotation;	// Relative to parent
	SC_Vector mScale;		// Relative to parent

	std::string mName;
};

class Editor_AssimpScene
{
public:
	Editor_AssimpScene() {}
	~Editor_AssimpScene() {}

	bool Init(const aiScene* aScene)
	{
		const uint32 numMaterials = aScene->mNumMaterials;
		mMaterials.Respace(numMaterials);
		for (uint32 i = 0; i < numMaterials; ++i)
		{
			if (!mMaterials[i].Init(aScene->mMaterials[i]))
				return false;
		}

		const uint32 numMeshes = aScene->mNumMeshes;
		SC_Array<SC_Future<bool>> tasks(numMeshes);
		mMeshes.Respace(numMeshes);
		for (uint32 i = 0; i < numMeshes; ++i)
			tasks.Add(SC_CreateFrameTask(std::bind(&Editor_AssimpMesh::Init, &mMeshes[i], aScene->mMeshes[i]))); // TODO: Long Task

		for (SC_Future<bool>& task : tasks)
			task.Wait();

		if (!mRootEntity.Init(aScene->mRootNode))
			return false;

		return true;
	}

private:
	SC_Array<Editor_AssimpMaterial> mMaterials;
	SC_Array<Editor_AssimpMesh> mMeshes;
	Editor_AssimpEntity mRootEntity;
};

Editor_AssetImporter_Assimp::Editor_AssetImporter_Assimp()
{

}

Editor_AssetImporter_Assimp::~Editor_AssetImporter_Assimp()
{

}

bool Editor_AssetImporter_Assimp::ImportScene(const std::string& aFilename)
{
	// Import data
	Editor_AssimpScene scene;
	{
		Assimp::Importer importer;

		uint32 flags = aiProcessPreset_TargetRealtime_MaxQuality | aiProcess_ConvertToLeftHanded;
		const aiScene* importedScene = importer.ReadFile(std::filesystem::absolute(aFilename).string(), flags);
		if (!importedScene)
			return false;

		if (!scene.Init(importedScene))
			return false;
	}

	// Use Imported Scene to build engine data


	return true;
}

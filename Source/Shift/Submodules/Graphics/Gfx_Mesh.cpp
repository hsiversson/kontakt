//ProjectFilter(Mesh)
#include "Graphics_Precompiled.h"
#include "Gfx_Mesh.h"

Gfx_Mesh::Gfx_Mesh()
	: mUseMeshlets(false)
{

}

Gfx_Mesh::~Gfx_Mesh()
{

}

const SR_VertexLayout& Gfx_Mesh::GetVertexLayout() const
{
	return mVertexLayout;
}

SR_BufferResource* Gfx_Mesh::GetVertexBufferResource() const
{
	return mVertexBufferResource;
}

SR_Buffer* Gfx_Mesh::GetVertexBuffer() const
{
	return mVertexBuffer;
}

SR_BufferResource* Gfx_Mesh::GetIndexBufferResource() const
{
	return mIndexBufferResource;
}

SR_Buffer* Gfx_Mesh::GetIndexBuffer() const
{
	return mIndexBuffer;
}

#if SR_ENABLE_MESH_SHADERS
const SGfx_MeshletBuffers& Gfx_Mesh::GetMeshletBuffers() const
{
	return mMeshletBuffers;
}

bool Gfx_Mesh::IsUsingMeshlets() const
{
	return mUseMeshlets;
}
#endif //SR_ENABLE_MESH_SHADERS

const SC_AABB& Gfx_Mesh::GetBoundingBox() const
{
	return mBoundingBox;
}

bool Gfx_Mesh::Init(const Gfx_MeshCreateProperties& aCreateProperties)
{
	SR_BufferResourceProperties resourceProps;
	resourceProps.mBindFlags = SR_BufferBindFlag_VertexBuffer | SR_BufferBindFlag_Buffer;
	resourceProps.mElementSize = SC_Max(aCreateProperties.mVertexLayout.GetVertexStrideSize(), 1);
	resourceProps.mElementCount = aCreateProperties.mVertexData.Count() / resourceProps.mElementSize;
	resourceProps.mWritable = false;
	mVertexBufferResource = SR_RenderDevice::gInstance->CreateBufferResource(resourceProps, aCreateProperties.mVertexData.GetBuffer());

	SR_BufferProperties bufferProps;
	bufferProps.mElementCount = mVertexBufferResource->GetProperties().mElementCount * mVertexBufferResource->GetProperties().mElementSize;
	bufferProps.mType = SR_BufferType::Bytes;
	mVertexBuffer = SR_RenderDevice::gInstance->CreateBuffer(bufferProps, mVertexBufferResource);

#if SR_ENABLE_MESH_SHADERS
	if (SR_RenderDevice::gInstance->mCaps.mMeshShaders && aCreateProperties.mUseMeshlets)
	{
		if (!InitMeshlet(aCreateProperties))
		{
			SC_ERROR("Couldn't initialize mesh for Meshlet Pipeline.");
			return false;
		}
	}
	else
#endif //SR_ENABLE_MESH_SHADERS
	{
		if (!InitDefault(aCreateProperties))
		{
			SC_ERROR("Couldn't initialize mesh for Default Geometry Pipeline.");
			return false;
		}
	}

#if SR_ENABLE_RAYTRACING
	//if (aCreateProperties.mIncludeInRaytracingWorld)
	//{
	//	if (!InitAccelerationStructure(aCreateProperties))
	//	{
	//		SC_ERROR("Couldn't initialize mesh acceleration structure.");
	//		return false;
	//	}
	//}
#endif

	mVertexLayout = aCreateProperties.mVertexLayout;
	mBoundingBox.mMin = aCreateProperties.mBoundingBox.mMin;
	mBoundingBox.mMax = aCreateProperties.mBoundingBox.mMax;
	return true;
}

bool Gfx_Mesh::InitDefault(const Gfx_MeshCreateProperties& aCreateParams)
{
	SR_BufferResourceProperties resourceProps;
	resourceProps.mBindFlags = SR_BufferBindFlag_IndexBuffer | SR_BufferBindFlag_Buffer;
	resourceProps.mWritable = false;

	SC_Array<uint8> indices;
	uint32 indexStride;
	Gfx_FlattenMeshletPrimitivesToIndexBuffer(aCreateParams.mMeshlets, aCreateParams.mPrimitiveIndices, aCreateParams.mVertexIndices, aCreateParams.mVertexIndicesStride, indices, indexStride);

	resourceProps.mElementCount = indices.Count() / indexStride;
	resourceProps.mElementSize = indexStride;
	mIndexBufferResource = SR_RenderDevice::gInstance->CreateBufferResource(resourceProps, indices.GetBuffer());

	return (mIndexBufferResource != nullptr);
}

#if SR_ENABLE_MESH_SHADERS
bool Gfx_Mesh::InitMeshlet(const Gfx_MeshCreateProperties& aCreateParams)
{
	SR_BufferProperties bufferProps;
	bufferProps.mElementCount = mVertexBufferResource->GetProperties().mElementCount;
	bufferProps.mType = SR_BufferType::Structured;
	mMeshletBuffers.mVertexBuffer = SR_RenderDevice::gInstance->CreateBuffer(bufferProps, mVertexBufferResource);

	SR_BufferResourceProperties bufferResourceProps;
	bufferResourceProps.mBindFlags = SR_BufferBindFlag_Buffer;
	bufferResourceProps.mElementCount = aCreateParams.mMeshlets.Count();
	bufferResourceProps.mElementSize = aCreateParams.mMeshlets.ElementStride();
	if (SC_Ref<SR_BufferResource> meshletBuffer = SR_RenderDevice::gInstance->CreateBufferResource(bufferResourceProps, aCreateParams.mMeshlets.GetBuffer()))
	{
		bufferProps.mElementCount = aCreateParams.mMeshlets.Count();
		mMeshletBuffers.mMeshletBuffer = SR_RenderDevice::gInstance->CreateBuffer(bufferProps, meshletBuffer);
	}
	else
		return false;

	bufferResourceProps.mElementCount = aCreateParams.mPrimitiveIndices.Count();
	bufferResourceProps.mElementSize = aCreateParams.mPrimitiveIndices.ElementStride();
	if (SC_Ref<SR_BufferResource> primitiveIndexBuffer = SR_RenderDevice::gInstance->CreateBufferResource(bufferResourceProps, aCreateParams.mPrimitiveIndices.GetBuffer()))
	{
		bufferProps.mElementCount = aCreateParams.mPrimitiveIndices.Count();
		mMeshletBuffers.mPrimitiveIndexBuffer = SR_RenderDevice::gInstance->CreateBuffer(bufferProps, primitiveIndexBuffer);
	}
	else
		return false;

	bufferResourceProps.mElementCount = aCreateParams.mVertexIndices.Count() / aCreateParams.mVertexIndicesStride;
	bufferResourceProps.mElementSize = aCreateParams.mVertexIndicesStride;
	if (SC_Ref<SR_BufferResource> vertexIndexBuffer = SR_RenderDevice::gInstance->CreateBufferResource(bufferResourceProps, aCreateParams.mVertexIndices.GetBuffer()))
	{
		bufferProps.mType = SR_BufferType::Default;
		bufferProps.mFormat = (aCreateParams.mVertexIndicesStride == sizeof(uint16)) ? SR_Format::R16_UINT : SR_Format::R32_UINT;
		bufferProps.mElementCount = bufferResourceProps.mElementCount;
		mMeshletBuffers.mVertexIndexBuffer = SR_RenderDevice::gInstance->CreateBuffer(bufferProps, vertexIndexBuffer);
	}
	else
		return false;

	mUseMeshlets = true;
	return true;
}
#endif //SR_ENABLE_MESH_SHADERS
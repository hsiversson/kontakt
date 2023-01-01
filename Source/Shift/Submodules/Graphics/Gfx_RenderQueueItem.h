//ProjectFilter(View)
#pragma once

class SR_PipelineState;
class SR_BufferResource;

struct SR_RasterizerState;
struct SR_BlendState;
class SR_Buffer;

struct Gfx_RenderQueueItemMeshletData
{
	operator bool() const
	{
		return (mVertexBuffer && mMeshletBuffer && mVertexIndexBuffer && mPrimitiveIndexBuffer);
	}

	SR_Buffer* mVertexBuffer;
	SR_Buffer* mMeshletBuffer;
	SR_Buffer* mVertexIndexBuffer;
	SR_Buffer* mPrimitiveIndexBuffer;
};

struct Gfx_RenderQueueItem
{
	Gfx_RenderQueueItem()
	{
		SC_ZeroMemory(this, sizeof(*this));
	}

	union
	{
		struct
		{
			SR_BufferResource* mVertexBuffer;
			SR_BufferResource* mIndexBuffer;
		};
		Gfx_RenderQueueItemMeshletData mMeshletData;
	};

	SC_Matrix mTransform;
	SC_Matrix mPrevTransform;

	uint32 mMaterialIndex;

	SR_RasterizerState* mRasterizerState;
	SR_BlendState* mBlendState;

	SR_PipelineState* mShader;

	float mSortDistance;
	uint32 mBaseInstanceDataOffset;
	uint16 mNumInstances;

	bool mUseMeshlets;
};
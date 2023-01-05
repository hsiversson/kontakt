//ProjectFilter(View)
#include "Graphics_Precompiled.h"
#include "Gfx_RenderQueue.h"

Gfx_RenderQueue::Gfx_RenderQueue(const SortType& aSortType)
	: mSortType(aSortType)
	, mIsPrepared(false)
{

}

Gfx_RenderQueue::~Gfx_RenderQueue()
{

}

void Gfx_RenderQueue::Prepare(Gfx_ViewRenderData& /*aPrepareData*/)
{
	SC_ASSERT(!mIsPrepared);

	Gfx_RenderQueueItem* items = mItems.GetBuffer();
	uint32 numItemsRemaining = mItems.Count();
	if (!numItemsRemaining)
		return;

	Sort();

	SC_Array<InstanceData> instanceDatas;
	while (numItemsRemaining)
	{
		Gfx_RenderQueueItem& firstItem = *items;
		uint32 numInstances = 1;

		SR_RasterizerState* rasterState = firstItem.mRasterizerState;
		SR_BlendState* blendState = firstItem.mBlendState;

		bool isItemValid = (firstItem.mVertexBuffer && firstItem.mIndexBuffer);
#if SR_ENABLE_MESH_SHADERS
		isItemValid = (firstItem.mUseMeshlets) ? firstItem.mMeshletData : isItemValid;
#endif //SR_ENABLE_MESH_SHADERS

		if (isItemValid)
		{
			InstanceData& firstInstanceData = instanceDatas.Add();
			firstInstanceData.mTransform = firstItem.mTransform;
			firstInstanceData.mPrevTransform = firstItem.mPrevTransform;
			firstInstanceData.mMaterialIndex = firstItem.mMaterialIndex;

			for (uint32 i = 1; i < numItemsRemaining; ++i)
			{
				Gfx_RenderQueueItem& nextItem = items[i];
				if (nextItem.mRasterizerState != rasterState ||
					nextItem.mBlendState != blendState ||
					numInstances != SC_UINT16_MAX)
					break;

#if SR_ENABLE_MESH_SHADERS
				if (firstItem.mUseMeshlets && (nextItem.mMeshletData != firstItem.mMeshletData))
					break;
				else
#endif //SR_ENABLE_MESH_SHADERS
				{
					if ((nextItem.mVertexBuffer != firstItem.mVertexBuffer) || (nextItem.mIndexBuffer != firstItem.mIndexBuffer))
						break;
				}

				InstanceData& instanceData = instanceDatas.Add();
				instanceData.mTransform = nextItem.mTransform;
				instanceData.mPrevTransform = nextItem.mPrevTransform;
				instanceData.mMaterialIndex = nextItem.mMaterialIndex;
				++numInstances;
			}
		}

		//aPrepareData.mInstanceData->Add(firstItem.mBaseInstanceDataOffset, instanceDatas.GetByteSize() / sizeof(SC_Vector4f), reinterpret_cast<const SC_Vector4*>(instanceDatas.GetBuffer()));

		firstItem.mNumInstances = uint16(numInstances);
		items += numInstances;
		numItemsRemaining -= numInstances;
		instanceDatas.RemoveAll();
	}

	mIsPrepared = true;
}

void Gfx_RenderQueue::Render(SR_CommandList* aCmdList) const
{

	uint32 numItemsRemaining = mItems.Count();
	if (!numItemsRemaining)
		return;

	SC_ASSERT(mIsPrepared);

	// Create temp instance buffer data

	const Gfx_RenderQueueItem* items = mItems.GetBuffer();
	while (numItemsRemaining)
	{
		const Gfx_RenderQueueItem& item = *items;
		uint32 numInstances = item.mNumInstances;

#if SR_ENABLE_MESH_SHADERS
		if (item.mUseMeshlets)
		{
			if (item.mMeshletData)
			{
				static constexpr uint32 gMaxGroupDispatchCount = 65536;
				float groupsPerInstance = (float)item.mMeshletData.mMeshletBuffer->GetProperties().mElementCount;
				uint32 maxInstancePerBatch = static_cast<uint32>(float(gMaxGroupDispatchCount) / groupsPerInstance);
				uint32 dispatchCount = (numInstances + maxInstancePerBatch - 1) / maxInstancePerBatch;

				for (uint32 i = 0; i < dispatchCount; ++i)
				{
					uint32 instanceOffset = maxInstancePerBatch * i;
					uint32 instanceCount = SC_Min(numInstances - instanceOffset, maxInstancePerBatch);

					//SGfx_MeshShadingDrawInfoStruct drawInfo;
					//drawInfo.mVertexBufferDescriptorIndex = item.mMeshletData.mVertexBuffer->GetDescriptorHeapIndex();
					//drawInfo.mMeshletBufferDescriptorIndex = item.mMeshletData.mMeshletBuffer->GetDescriptorHeapIndex();
					//drawInfo.mVertexIndexBufferDescriptorIndex = item.mMeshletData.mVertexIndexBuffer->GetDescriptorHeapIndex();
					//drawInfo.mPrimitiveIndexBufferDescriptorIndex = item.mMeshletData.mPrimitiveIndexBuffer->GetDescriptorHeapIndex();
					//drawInfo.mBaseInstanceDataOffset = item.mBaseInstanceDataOffset;
					//drawInfo.mInstanceDataByteSize = sizeof(InstanceData);
					//drawInfo.mNumInstances = instanceCount;
					//drawInfo.mInstanceOffset = instanceOffset;
					//drawInfo.mNumMeshlets = item.mMeshletData.mMeshletBuffer->GetProperties().mElementCount;

					//uint64 cbOffset = 0;
					//SR_BufferResource* cb = aCmdList->GetBufferResource(cbOffset, SR_BufferBindFlag_ConstantBuffer, sizeof(drawInfo), &drawInfo, 1);
					//aCmdList->SetRootConstantBuffer(cb, cbOffset, 0);

					aCmdList->SetPipelineState(item.mPipelineState);
					aCmdList->SetPrimitiveTopology(SR_PrimitiveTopology::TriangleList);

					uint32 groupCount = static_cast<uint32>(ceilf(groupsPerInstance * instanceCount));
					aCmdList->Dispatch(groupCount, 1, 1);
				}
			}
		}
		else
#endif //SR_ENABLE_MESH_SHADERS
		{
			SR_BufferResource* vertexBuffer = item.mVertexBuffer;
			SR_BufferResource* indexBuffer = item.mIndexBuffer;
			if (vertexBuffer && indexBuffer)
			{
				//Gfx_VertexShadingDrawInfoStruct constants;
				//constants.mBaseInstanceDataOffset = item.mBaseInstanceDataOffset;
				//constants.mInstanceDataByteSize = sizeof(InstanceData);
				//constants.mInstanceOffset = 0;
				//
				//uint64 cbOffset = 0;
				//SR_BufferResource* cb = aCmdList->GetBufferResource(cbOffset, SR_BufferBindFlag_ConstantBuffer, sizeof(constants), &constants, 1);
				//aCmdList->SetRootConstantBuffer(cb, cbOffset, 0);

				aCmdList->SetVertexBuffer(vertexBuffer);
				aCmdList->SetIndexBuffer(indexBuffer);
				aCmdList->SetPipelineState(item.mPipelineState);
				aCmdList->SetPrimitiveTopology(SR_PrimitiveTopology::TriangleList);
				aCmdList->DrawIndexedInstanced(indexBuffer->GetProperties().mElementCount, numInstances);
			}
		}

		items += numInstances;
		numItemsRemaining -= numInstances;
	}
}

void Gfx_RenderQueue::Clear()
{
	mItems.RemoveAll();
	mIsPrepared = false;
}

SC_Mutex& Gfx_RenderQueue::GetMutex()
{
	return mMutex;
}

Gfx_RenderQueueItem& Gfx_RenderQueue::AddItem()
{
	return mItems.Add();
}

Gfx_RenderQueueItem& Gfx_RenderQueue::AddItem(const Gfx_RenderQueueItem& aItem)
{
	return mItems.Add(aItem);
}

void Gfx_RenderQueue::AddItems(const Gfx_RenderQueueItem* aItems, uint32 aNumItems)
{
	mItems.Add(aItems, aNumItems);
}

uint32 Gfx_RenderQueue::NumItems() const
{
	return mItems.Count();
}

bool Gfx_RenderQueue::IsEmpty() const
{
	return mItems.IsEmpty();
}

void Gfx_RenderQueue::Sort()
{
	switch (mSortType)
	{
	case SortType::ByState:
		Sort_ByState();
		break;
	case SortType::FarFirst:
		Sort_FarFirst();
		break;
	case SortType::NearFirst:
		Sort_NearFirst();
		break;
	}
}

void Gfx_RenderQueue::Sort_ByState()
{
	auto Comparison = [](const Gfx_RenderQueueItem& aLeft, const Gfx_RenderQueueItem& aRight)
	{
		if (aLeft.mUseMeshlets != aRight.mUseMeshlets)
			return aLeft.mUseMeshlets < aRight.mUseMeshlets;

		if (aLeft.mRasterizerState != aRight.mRasterizerState)
			return aLeft.mRasterizerState < aRight.mRasterizerState;

		if (aLeft.mBlendState != aRight.mBlendState)
			return aLeft.mBlendState < aRight.mBlendState;

		if (aLeft.mPipelineState != aRight.mPipelineState)
			return aLeft.mPipelineState < aRight.mPipelineState;

		if (aLeft.mVertexBuffer != aRight.mVertexBuffer)
			return aLeft.mVertexBuffer < aRight.mVertexBuffer;

		if (aLeft.mIndexBuffer != aRight.mIndexBuffer)
			return aLeft.mIndexBuffer < aRight.mIndexBuffer;

		return aLeft.mSortDistance < aRight.mSortDistance;
	};

	std::sort(mItems.begin(), mItems.end(), Comparison);
}

void Gfx_RenderQueue::Sort_FarFirst()
{
	auto Comparison = [](const Gfx_RenderQueueItem& aLeft, const Gfx_RenderQueueItem& aRight)
	{
		if (aLeft.mSortDistance != aRight.mSortDistance)
			return aLeft.mSortDistance > aRight.mSortDistance;

		if (aLeft.mUseMeshlets != aRight.mUseMeshlets)
			return aLeft.mUseMeshlets < aRight.mUseMeshlets;

		if (aLeft.mRasterizerState != aRight.mRasterizerState)
			return aLeft.mRasterizerState < aRight.mRasterizerState;

		if (aLeft.mBlendState != aRight.mBlendState)
			return aLeft.mBlendState < aRight.mBlendState;

		if (aLeft.mPipelineState != aRight.mPipelineState)
			return aLeft.mPipelineState < aRight.mPipelineState;

		if (aLeft.mVertexBuffer != aRight.mVertexBuffer)
			return aLeft.mVertexBuffer < aRight.mVertexBuffer;

		return aLeft.mIndexBuffer < aRight.mIndexBuffer;
	};

	std::sort(mItems.begin(), mItems.end(), Comparison);
}

void Gfx_RenderQueue::Sort_NearFirst()
{
	auto Comparison = [](const Gfx_RenderQueueItem& aLeft, const Gfx_RenderQueueItem& aRight)
	{
		if (aLeft.mSortDistance != aRight.mSortDistance)
			return aLeft.mSortDistance < aRight.mSortDistance;

		if (aLeft.mUseMeshlets != aRight.mUseMeshlets)
			return aLeft.mUseMeshlets < aRight.mUseMeshlets;

		if (aLeft.mRasterizerState != aRight.mRasterizerState)
			return aLeft.mRasterizerState < aRight.mRasterizerState;

		if (aLeft.mBlendState != aRight.mBlendState)
			return aLeft.mBlendState < aRight.mBlendState;

		if (aLeft.mPipelineState != aRight.mPipelineState)
			return aLeft.mPipelineState < aRight.mPipelineState;

		if (aLeft.mVertexBuffer != aRight.mVertexBuffer)
			return aLeft.mVertexBuffer < aRight.mVertexBuffer;

		return aLeft.mIndexBuffer < aRight.mIndexBuffer;
	};

	std::sort(mItems.begin(), mItems.end(), Comparison);
}

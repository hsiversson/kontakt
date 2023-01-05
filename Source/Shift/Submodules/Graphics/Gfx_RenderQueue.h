//ProjectFilter(View)
#pragma once
#include "Gfx_RenderQueueItem.h"

struct Gfx_ViewRenderData;

class Gfx_RenderQueue
{
public:
	enum class SortType
	{
		Default,
		ByState = Default,
		FarFirst,
		NearFirst
	};

	Gfx_RenderQueue(const SortType& aSortType);
	virtual ~Gfx_RenderQueue();

	void Prepare(Gfx_ViewRenderData& aPrepareData);
	void Render(SR_CommandList* aCmdList) const;
	void Clear();

	SC_Mutex& GetMutex();

	Gfx_RenderQueueItem& AddItem();
	Gfx_RenderQueueItem& AddItem(const Gfx_RenderQueueItem& aItem);
	void AddItems(const Gfx_RenderQueueItem* aItems, uint32 aNumItems);

	uint32 NumItems() const;
	bool IsEmpty() const;

private:
	struct alignas(16) InstanceData
	{
		SC_Matrix mTransform;
		SC_Matrix mPrevTransform;
		uint32 mMaterialIndex;
		uint32 __pad[3];
	};

	void Sort();
	void Sort_ByState();
	void Sort_FarFirst();
	void Sort_NearFirst();

private:
	SC_Array<Gfx_RenderQueueItem> mItems;
	SC_Mutex mMutex;
	const SortType mSortType;
	bool mIsPrepared;
};

class Gfx_RenderQueue_ByState final : public Gfx_RenderQueue
{
public:
	Gfx_RenderQueue_ByState() : Gfx_RenderQueue(Gfx_RenderQueue::SortType::ByState) {}
};

class Gfx_RenderQueue_FarFirst final : public Gfx_RenderQueue
{
public:
	Gfx_RenderQueue_FarFirst() : Gfx_RenderQueue(Gfx_RenderQueue::SortType::FarFirst) {}
};

class Gfx_RenderQueue_NearFirst final : public Gfx_RenderQueue
{
public:
	Gfx_RenderQueue_NearFirst() : Gfx_RenderQueue(Gfx_RenderQueue::SortType::NearFirst) {}
};
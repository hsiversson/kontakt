//ProjectFilter(Containers)
#pragma once

template<class T>
class SC_Queue
{
public:
	SC_Queue();
	SC_Queue(const SC_Queue& aOther) = delete;
	SC_Queue(SC_Queue&& aOther);
	~SC_Queue();

	void operator=(const SC_Queue& aOther) = delete;

	bool IsEmpty() const;
	uint32 Count() const;
	int32 ICount() const;
	uint32 Capacity() const;

	void Reserve(uint32 aCount);
	void ReserveAdditional(uint32 aCount);

	T& Add();
	T& Add(const T& aItem);
	void Add(const SC_Array<T>& aItems);
	void Add(const T* aItems, uint32 aNumItems);

	T& Peek() const;
	bool Pop(T& aOutItem);
	T Pop();

	T& operator[](uint32 aIndex);
	const T& operator[](uint32 aIndex) const;

	void Remove();
	void RemoveAll();
	void Clear();

private:
	T* mInternalItemBuffer;
	uint32 mItemCapacity;
	uint32 mCurrentItemCount;
	uint32 mReadIndex;
	uint32 mWriteIndex;
};

template<class T>
inline SC_Queue<T>::SC_Queue()
	: mInternalItemBuffer(nullptr)
	, mItemCapacity(1)
	, mCurrentItemCount(0)
	, mReadIndex(0)
	, mWriteIndex(0)
{
}

template<class T>
inline SC_Queue<T>::SC_Queue(SC_Queue&& aOther)
	: mInternalItemBuffer(aOther.mInternalItemBuffer)
	, mItemCapacity(aOther.mItemCapacity)
	, mCurrentItemCount(aOther.mCurrentItemCount)
	, mReadIndex(aOther.mReadIndex)
	, mWriteIndex(aOther.mWriteIndex)
{
	aOther.mInternalItemBuffer = nullptr;
	aOther.mItemCapacity = 1;
	aOther.mCurrentItemCount = 0;
	aOther.mReadIndex = 0;
	aOther.mWriteIndex = 0;
}

template<class T>
inline SC_Queue<T>::~SC_Queue()
{
	RemoveAll();
	delete[] (char*)mInternalItemBuffer;
}

template<class T>
inline bool SC_Queue<T>::IsEmpty() const
{
	return mCurrentItemCount == 0;
}

template<class T>
inline uint32 SC_Queue<T>::Count() const
{
	return mCurrentItemCount;
}

template<class T>
inline int32 SC_Queue<T>::ICount() const
{
	return int32(mCurrentItemCount);
}

template<class T>
inline uint32 SC_Queue<T>::Capacity() const
{
	return mItemCapacity;
}

template<class T>
inline void SC_Queue<T>::Reserve(uint32 aCount)
{
	if (aCount <= mItemCapacity)
		return;

	T* newBuffer = (T*) new char[aCount * sizeof(T)];

	uint32 count = 0;
	if (mCurrentItemCount > 0)
	{
		uint32 read = mReadIndex;
		uint32 write = mWriteIndex;
		if (read < write || (read == write && read == 0))
		{
			count = mCurrentItemCount;
			SC_RelocateN(newBuffer, mInternalItemBuffer + read, count);
		}
		else
		{
			uint32 endCount = mItemCapacity - read;
			count = endCount + write;
			SC_ASSERT(count == Count());
			SC_RelocateN(newBuffer, mInternalItemBuffer + read, endCount);
			SC_RelocateN(newBuffer + endCount, mInternalItemBuffer, write);
		}
	}

	delete[] (char*)mInternalItemBuffer;
	mInternalItemBuffer = newBuffer;
	mItemCapacity = aCount;
	mReadIndex = 0;
	mWriteIndex = count;
}

template<class T>
inline void SC_Queue<T>::ReserveAdditional(uint32 aCount)
{
	if (mItemCapacity <= 1)
	{
		Reserve(32);
		return;
	}

	const uint32 requiredCapacity = mCurrentItemCount + aCount;
	if (requiredCapacity <= mItemCapacity)
		return;

	const uint32 newCapacity = SC_Max(requiredCapacity, (mCurrentItemCount + (mCurrentItemCount + 1) / 2));
	Reserve(newCapacity);
}

template<class T>
inline T& SC_Queue<T>::Add()
{
	ReserveAdditional(1);

	uint32 write = mWriteIndex;
	uint32 next = write + 1;
	if (next == mItemCapacity)
		next = 0;

	new (static_cast<void*>(mInternalItemBuffer + write)) T();
	mWriteIndex = next;

	++mCurrentItemCount;
	return *(mInternalItemBuffer + write);
}

template<class T>
inline T& SC_Queue<T>::Add(const T& aItem)
{
	ReserveAdditional(1);

	uint32 write = mWriteIndex;
	uint32 next = write + 1;
	if (next == mItemCapacity)
		next = 0;

	new (static_cast<void*>(mInternalItemBuffer + write)) T(aItem);
	mWriteIndex = next;

	++mCurrentItemCount;
	return *(mInternalItemBuffer + write);
}

template<class T>
inline void SC_Queue<T>::Add(const SC_Array<T>& aItems)
{
	Add(aItems.GetBuffer(), aItems.Count());
}

template<class T>
inline void SC_Queue<T>::Add(const T* aItems, uint32 aNumItems)
{
	ReserveAdditional(aNumItems);
	for (uint32 i = 0; i < aNumItems; ++i)
		Add(aItems[i]);
}

template<class T>
inline T& SC_Queue<T>::Peek() const
{
	SC_ASSERT(mReadIndex != mWriteIndex);
	return mInternalItemBuffer[mReadIndex];
}

template<class T>
inline bool SC_Queue<T>::Pop(T& aOutItem)
{
	if (!IsEmpty())
	{
		aOutItem = Peek();
		Remove();
		return true;
	}
	else
		return false;
}

template<class T>
inline T SC_Queue<T>::Pop()
{
	SC_ASSERT(!IsEmpty());

	T item = Peek();
	Remove();
	return item;
}

template<class T>
inline T& SC_Queue<T>::operator[](uint32 aIndex)
{
	return mInternalItemBuffer[(mReadIndex + aIndex) % mItemCapacity];
}

template<class T>
inline const T& SC_Queue<T>::operator[](uint32 aIndex) const
{
	return mInternalItemBuffer[(mReadIndex + aIndex) % mItemCapacity];
}

template<class T>
inline void SC_Queue<T>::Remove()
{
	SC_ASSERT(mReadIndex != mWriteIndex);

	(mInternalItemBuffer + mReadIndex)->~T();

	uint32 read = mReadIndex + 1;
	mReadIndex = (read == mItemCapacity) ? 0 : read;
	mCurrentItemCount--;
}

template<class T>
inline void SC_Queue<T>::RemoveAll()
{
	while (mReadIndex != mWriteIndex)
		Remove();
}

template<class T>
inline void SC_Queue<T>::Clear()
{
	mReadIndex = 0;
	mWriteIndex = 0;
	mCurrentItemCount = 0;
}

template<class T>
struct SC_AllowMemcpyRelocation<SC_Queue<T>>
{
	static const bool mValue = true;
};
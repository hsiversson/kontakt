//ProjectFilter(Interface/Resources)
#pragma once
#include "SR_TrackedResource.h"

struct SR_BufferResourceProperties
{
	SR_BufferResourceProperties() : mFormat(SR_Format::UNKNOWN), mElementSize(0), mElementCount(0), mBindFlags(0), mInitialData(nullptr), mWritable(false), mIsUploadBuffer(false), mDebugName(nullptr) {}

	SR_Format mFormat;
	uint32 mElementSize;
	uint32 mElementCount;
	uint32 mBindFlags;

	const void* mInitialData;

	bool mWritable;
	bool mIsUploadBuffer;

	const char* mDebugName;
};

class SR_BufferResource : public SR_TrackedResource
{
public:
	virtual ~SR_BufferResource();

	void UpdateData(uint32 aOffset, const void* aData, uint64 aSize);
	void* GetDataPtr() const;

	const SR_BufferResourceProperties& GetProperties() const;

protected:
	SR_BufferResource(const SR_BufferResourceProperties& aProperties);

	SR_BufferResourceProperties mProperties;
	uint8* mDataPtr;
};
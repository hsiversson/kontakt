//ProjectFilter(Interface/Resources)
#pragma once
#include "SR_TrackedResource.h"

struct SR_TextureSection
{
	SR_TextureSection() : mMostDetailedMip(0), mNumMips(0), mFirstArrayIndex(0), mArraySize(0) {}

	bool operator==(const SR_TextureSection& aOther) const { return mMostDetailedMip == aOther.mMostDetailedMip && mNumMips == aOther.mNumMips && mFirstArrayIndex == aOther.mFirstArrayIndex && mArraySize == aOther.mArraySize; }
	bool operator!=(const SR_TextureSection& aOther) const { return !(*this == aOther); }

	uint8 mMostDetailedMip;
	uint16 mNumMips;
	uint16 mFirstArrayIndex;
	uint16 mArraySize;
};

struct SR_TextureResourceProperties
{
	SC_Vector3i mSize;
	SR_Format mFormat;
	uint16 mNumMips;
	uint16 mArraySize;

	SR_ResourceType mType;

	bool mAllowRenderTarget;
	bool mAllowDepthStencil;
	bool mAllowWrites;

	std::string mDebugName;
};

struct SR_PixelData
{
	SR_PixelData() : mData(nullptr), mBytesPerLine(0), mBytesPerSlice(0), mSize(0) {}

	//SR_TextureLevel mLevel;
	uint8* mData;
	uint32 mBytesPerLine;
	uint32 mBytesPerSlice;
	uint32 mSize;

	operator void* () const { return mData; }
};

class SR_TextureResource : public SR_TrackedResource
{
public:
	virtual ~SR_TextureResource();

	const SR_TextureResourceProperties& GetProperties() const;

protected:
	SR_TextureResource(const SR_TextureResourceProperties& aProperties);

	SR_TextureResourceProperties mProperties;
};
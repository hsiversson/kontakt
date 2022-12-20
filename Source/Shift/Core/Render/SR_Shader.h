//ProjectFilter(Interface/Shader)
#pragma once
#include "SR_Resource.h"

struct SR_CreateShaderProperties
{
	const char* mFileName;
	const char* mEntryPoint;

	SR_ShaderType mType;
};

struct SR_ShaderMetaData
{
	SC_Vector3ui mNumThreads;
};

struct SR_ShaderByteCode
{
	SR_ShaderByteCode() : mSize(0), mData(nullptr) {}
	SR_ShaderByteCode(const SR_ShaderByteCode& aOther)
		: mSize(aOther.mSize)
		, mData(nullptr)
	{
		if (mSize > 0 || aOther.mData == nullptr)
		{
			mData = new uint8[mSize];
			SC_Memcpy(mData, aOther.mData, mSize);
		}
	}

	SR_ShaderByteCode& operator=(const SR_ShaderByteCode& aOther)
	{
		mSize = aOther.mSize;
		if (mSize > 0 || aOther.mData == nullptr)
		{
			mData = new uint8[mSize];
			SC_Memcpy(mData, aOther.mData, mSize);
		}
		return *this;
	}

	SC_SizeT mSize;
	uint8* mData;
	std::string mEntryPoint;
};

class SR_Shader : public SR_Resource
{
	friend class SR_RenderDevice_DX12;
public:
	SR_Shader();
	virtual ~SR_Shader();

	const SR_ShaderByteCode& GetByteCode() const;
	const SR_ShaderMetaData& GetMetaData() const;
	const SR_ShaderType& GetType() const;
protected:
	SR_ShaderByteCode mShaderByteCode;
	SR_ShaderMetaData mMetaData;
	SR_ShaderType mShaderType;
};


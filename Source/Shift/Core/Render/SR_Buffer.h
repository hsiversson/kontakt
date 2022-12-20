//ProjectFilter(Interface/Resources)
#pragma once
#include "SR_BufferResource.h"

enum class SR_BufferType
{
	Default,
	Bytes,
	Structured,
	RaytracingBuffer,
	COUNT
};

struct SR_BufferProperties
{
	SR_BufferProperties() : mFirstElement(0), mElementCount(0), mOffset(0), mFormat(SR_Format::UNKNOWN), mType(SR_BufferType::Default), mWritable(false) {}

	uint32 mFirstElement;
	uint32 mElementCount;
	uint32 mOffset;
	SR_Format mFormat;
	SR_BufferType mType;
	bool mWritable;
};

class SR_Buffer : public SR_Resource
{
public:
	virtual ~SR_Buffer();

	const SR_BufferProperties& GetProperties() const;
	const SR_BufferResourceProperties& GetResourceProperties() const;
	SR_BufferResource* GetResource() const;

	const SR_Descriptor& GetDescriptor() const;
	uint32 GetDescriptorHeapIndex() const;
	const SR_Descriptor& GetRWDescriptor() const;
	uint32 GetRWDescriptorHeapIndex() const;

protected:
	SR_Buffer(const SR_BufferProperties& aProperties, const SC_Ref<SR_BufferResource>& aResource);

	SR_BufferProperties mProperties;
	SC_StaticArray<SR_Descriptor, 2> mDescriptors; // [0]: Read, [1]: RW
	SC_Ref<SR_BufferResource> mResource;
};

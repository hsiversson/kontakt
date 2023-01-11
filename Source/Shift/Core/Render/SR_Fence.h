//ProjectFilter(Interface/Resources)
#pragma once
#include "SR_Resource.h"
#include "SR_RenderEnums.h"

class SR_FenceResource : public SR_Resource
{
public:
	SR_FenceResource() {}
	virtual ~SR_FenceResource() {}

	virtual bool IsPending(uint64 /*aValue*/) { return false; }
	virtual bool Wait(uint64 /*aValue*/, bool /*aBlock*/ = true) { return true; }
	virtual uint64 GetNextValue() = 0;
	virtual uint64 GetLatestValue() = 0;
};

struct SR_Fence
{
	uint64 mValue;
	SR_CommandListType mType;
};


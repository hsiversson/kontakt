//ProjectFilter(Memory)
#include "Platform_Precompiled.h"
#include "SC_Ref.h"

SC_ReferenceCounted::SC_ReferenceCounted()
	: mRefCount(0)
{

}

SC_ReferenceCounted::SC_ReferenceCounted(const SC_ReferenceCounted&)
	: mRefCount(0)
{

}

SC_ReferenceCounted& SC_ReferenceCounted::operator=(const SC_ReferenceCounted&)
{
	return *this;
}

void SC_ReferenceCounted::IncrementRef() const
{
	SC_Atomic::Increment_GetNew(mRefCount);
}

void SC_ReferenceCounted::DecrementRef() const
{
	for (;;)
	{
		uint32 currentCount = mRefCount;
		SC_ASSERT(currentCount > 0, "Trying to decrement count when it is already 0.");
		if (currentCount == 1)
		{
			if (const_cast<SC_ReferenceCounted*>(this)->CanDestruct(mRefCount))
				delete this;

			return;
		}

		if (SC_Atomic::CompareExchange(mRefCount, currentCount -1, currentCount))
			return;
	}
}

uint32 SC_ReferenceCounted::GetRefCount() const
{
	return mRefCount;
}

SC_ReferenceCounted::~SC_ReferenceCounted()
{
	SC_ASSERT(mRefCount == 0, "Reference Count is expected to be 0 but was {}", mRefCount);
}

bool SC_ReferenceCounted::CanDestruct(volatile uint32& aRefCount)
{
	return SC_Atomic::Decrement_GetNew(aRefCount) == 0;
}

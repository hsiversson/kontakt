//ProjectFilter(Misc)
#include "Platform_Precompiled.h"
#include "SC_Relocate.h"

#include <cstring>

void SC_Memcpy(void* aDst, const void* aSrc, SC_SizeT aSize)
{
	memcpy(aDst, aSrc, aSize);
}

void SC_Memmove(void* aDst, void* aSrc, SC_SizeT aSize)
{
	memmove(aDst, aSrc, aSize);
}

void SC_Memset(void* aDst, int aValue, SC_SizeT aSize)
{
	memset(aDst, aValue, aSize);
}

void SC_ZeroMemory(void* aDst, SC_SizeT aSize)
{
	memset(aDst, 0, aSize);
}

void SC_RelocateBytes(void* aDst, void* aSrc, size_t aCount)
{
	if (aDst == aSrc || aCount == 0)
		return;

	const ptrdiff_t signedDiff = uintptr_t(aDst) - uintptr_t(aSrc);
	const ptrdiff_t absDiff = (signedDiff >= 0) ? signedDiff : -signedDiff;

	if ((size_t)absDiff >= aCount)
		SC_Memcpy(aDst, aSrc, aCount);
	else
		SC_Memmove(aDst, aSrc, aCount);
}

//ProjectFilter(Misc)
#pragma once

inline uint32 SC_Align(uint32 aValue, uint32 aAlignment)
{
	return (aValue + aAlignment - 1) & ~(aAlignment - 1);
}

inline uint64 SC_Align(uint64 aValue, uint64 aAlignment)
{
	return (aValue + aAlignment - 1) & ~(aAlignment - 1);
}


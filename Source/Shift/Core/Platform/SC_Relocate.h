//ProjectFilter(Misc)
#pragma once
#include <new>

template<typename T>
struct SC_AllowMemcpyRelocation
{
	static const bool mValue = __has_trivial_destructor(T) || __is_trivial(T);
};

template <class T, bool AllowMemcpy> struct SC_RelocationUtility;

template <class T>
struct SC_RelocationUtility<T, false>
{
	static inline void Relocate(T* aDst, T* aSrc)
	{
		new (const_cast<typename SC_RemoveConst<T>::Type*>(aDst)) T(SC_Move(*aSrc));
		(aSrc)->~T();
	}

	static inline void RelocateN(T* aDst, T* aSrc, int aCount)
	{
		if (aDst == aSrc || !aCount)
			return;

		if (aDst < aSrc)
		{
			for (int i = 0; i < aCount; ++i)
			{
				Relocate(aDst + i, aSrc + i);
			}
		}
		else if (aSrc < aDst)
		{
			for (int i = aCount - 1; i >= 0; --i)
			{
				Relocate(aDst + i, aSrc + i);
			}
		}
	}
};

void SC_RelocateBytes(void* aDst, void* aSrc, size_t aCount);

template<class T>
inline void SC_Relocate(T* aDest, const T* aSrc)
{
	if (aDest == aSrc)
		return;

	SC_RelocationUtility<T, SC_AllowMemcpyRelocation<T>::mValue>::Relocate(aDst, aSrc);
}

template <class T>
inline void SC_RelocateN(T* aDst, const T* aSrc, int aCount)
{
	if (aDst == aSrc)
		return;

	SC_RelocationUtility<T, SC_AllowMemcpyRelocation<T>::mValue>::RelocateN(aDst, aSrc, aCount);
}

#define SC_ALLOW_MEMCPY_RELOCATE(aType)		\
	template<>								\
	struct SC_AllowMemcpyRelocation<aType> { static const bool mValue = true; }	
	
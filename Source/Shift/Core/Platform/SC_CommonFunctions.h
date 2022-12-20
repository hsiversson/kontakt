//ProjectFilter(Misc)
#pragma once
#include "SC_TypeTraits.h"

template <typename T>
inline typename SC_RemoveReference<T>::Type&& SC_Move(T&& aObj)
{
	using CastType = typename SC_RemoveReference<T>::Type;
	return (CastType&&)aObj;
}

template<class T>
inline void SC_FillN(T* aDestination, SC_SizeT aCount, const T& aValue)
{
	for (unsigned i = 0; i != aCount; ++i)
		aDestination[i] = aValue;
}

template<class T, int32 Count>
inline void SC_Fill(T(&aDestination)[Count], const T& aValue)
{
	for (int i = 0; i != Count; ++i)
		aDestination[i] = aValue;
}

template<class Type>
inline void SC_Construct(const Type* aDst)
{
	new (const_cast<typename SC_RemoveConst<Type>::Type*>(aDst)) Type();
}

template<class Type>
inline void SC_Construct(const Type* aDst, uint32 aCount)
{
	for (uint32 i = 0; i < aCount; ++i)
		new (const_cast<typename SC_RemoveConst<Type>::Type*>(aDst + i)) Type();
}

template<class Type>
inline void SC_Destruct(const Type* aDst)
{
	if (aDst)
		aDst->~Type();
}

template<class Type>
inline void SC_Destruct(const Type* aDst, uint32 aCount)
{
	if (!aDst)
		return;

	for (int32 i = (aCount - 1); i >= 0; --i)
		(aDst + i)->~Type();
}

template<class Type>
inline void SC_CopyConstruct(const Type* aDst, const Type& aSrc)
{
	new (const_cast<typename SC_RemoveConst<Type>::Type*>(aDst)) Type(aSrc);
}

template<class Type>
inline void SC_CopyConstruct(const Type* aDst, const Type* aSrc, uint32 aCount)
{
	for (uint32 i = 0; i < aCount; ++i)
		new (const_cast<typename SC_RemoveConst<Type>::Type*>(aDst + i)) Type(aSrc[i]);
}

template<class Type>
inline void SC_MoveConstruct(Type* aDst, Type* aSrc, uint32 aCount)
{
	for (uint32 i = 0; i < aCount; ++i)
		new (static_cast<void*>(aDst + i)) Type(SC_Move(aSrc[i]));
}
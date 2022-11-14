//ProjectFilter(Misc)
#pragma once
#include "SC_TypeTraits.h"



template <typename T>
inline typename SC_RemoveReference<T>::Type&& SC_Move(T&& aObj)
{
	using CastType = typename SC_RemoveReference<T>::Type;
	return (CastType&&)aObj;
}


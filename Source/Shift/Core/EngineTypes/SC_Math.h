//ProjectFilter(Math)
#pragma once

template <class Type1, class Type2>
inline Type1 SC_Min(const Type1& aFirst, const Type2& aSecond)
{
	return (aFirst < static_cast<Type1>(aSecond)) ? aFirst : static_cast<Type1>(aSecond);
}

template <class Type>
inline Type SC_Min(const Type& aFirst, const Type& aSecond, const Type& aThird)
{
	Type temp = SC_Min(aFirst, aSecond);
	return SC_Min(temp, aThird);
}

template <class Type1, class Type2>
inline Type1 SC_Max(const Type1& aFirst, const Type2& aSecond)
{
	return (aFirst < static_cast<Type1>(aSecond)) ? static_cast<Type1>(aSecond) : aFirst;
}

template<typename Type>
inline Type SC_Max(const Type& aFirst, const Type& aSecond, const Type& aThird)
{
	Type temp = SC_Max(aFirst, aSecond);
	return SC_Max(temp, aThird);
}

template<typename Type>
inline Type SC_Clamp(const Type& aValue, const Type& aMin, const Type& aMax)
{
	if (aValue < aMin)
		return aMin;
	else if (aMax < aValue)
		return aMax;
	else
		return aValue;
}

template<typename Type>
inline Type SC_Saturate(const Type& aValue)
{
	return SC_Clamp(aValue, static_cast<Type>(0), static_cast<Type>(1));
}

template<typename Type>
inline Type SC_Lerp(const Type& aA, const Type& aB, const Type& aT)
{
	return aA + aT * (aB - aA);
}

// Float Operations

inline 
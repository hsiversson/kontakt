//ProjectFilter(Math)
#pragma once
#include "SC_TypeDefines.h"

#define __SC_MATH_HEADER__

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

template<class T>
inline auto SC_RadiansToDegrees(T const& aRadVal) -> decltype(aRadVal* (180.f / SC_PI))
{
	return aRadVal * (180.f / SC_PI);
}

/* Converts degrees to radians. */
template<class T>
inline auto SC_DegreesToRadians(T const& aDegVal) -> decltype(aDegVal* (SC_PI / 180.f))
{
	return aDegVal * (SC_PI / 180.f);
}

template <typename T>
inline int Sign(T aValue)
{
	return (T(0) < aValue) - (aValue < T(0));
}

// Float Operations
float SC_Abs(float aVal);
float SC_Floor(float aVal);
float SC_Ceil(float aVal);
float SC_Round(float aVal);
float SC_Frac(float aVal);
float SC_Sin(float aVal);
float SC_Asin(float aVal);
float SC_Cos(float aVal);
float SC_Acos(float aVal);
void SC_SinCos(float& aOutSin, float& aOutCos, float aValue);
float SC_Tan(float aVal);
float SC_Atan(float aVal);
float SC_Atan2(float aY, float aX);
float SC_Sqrt(float aVal);
float SC_InvSqrt(float aVal);
float SC_Square(float aVal);
float SC_Log(float aVal);
float SC_Log2(float aVal);
float SC_Pow(float aVal, float aExp);
float SC_Exp(float aVal);
float SC_Exp2(float aVal);

// Vector
#include "SC_Vector.h"

// Matrix
#include "SC_Matrix.h"

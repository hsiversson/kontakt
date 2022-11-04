//ProjectFilter(Math)
#pragma once
#include "SC_TypeDefines.h"
#include <cmath>
#include <cfloat>

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
inline auto RadiansToDegrees(T const& aRadVal) -> decltype(aRadVal* (180.f / SC_PI))
{
	return aRadVal * (180.f / PI);
}

/* Converts degrees to radians. */
template<class T>
inline auto DegreesToRadians(T const& aDegVal) -> decltype(aDegVal* (SC_PI / 180.f))
{
	return aDegVal * (PI / 180.f);
}

template <typename T>
inline int Sign(T aValue)
{
	return (T(0) < aValue) - (aValue < T(0));
}

// Float Operations
inline float SC_Abs(float aVal)				{ return fabsf(aVal); }
inline float SC_Floor(float aVal)			{ return floorf(aVal); }
inline float SC_Ceil(float aVal)			{ return ceilf(aVal); }
inline float SC_Round(float aVal)			{ return roundf(aVal); }
inline float SC_Frac(float aVal)			{ float intPart = 0; return modf(aVal, &intPart); }
inline float SC_Sin(float aVal)				{ return sinf(aVal); }
inline float SC_Asin(float aVal)			{ return asinf(aVal); }
inline float SC_Cos(float aVal)				{ return cosf(aVal); }
inline float SC_Acos(float aVal)			{ return acosf(aVal); }
inline float SC_Tan(float aVal)				{ return tanf(aVal); }
inline float SC_Atan(float aVal)			{ return atanf(aVal); }
inline float SC_Atan2(float aY, float aX)	{ return atan2f(aY, aX); }
inline float SC_Sqrt(float aVal)			{ return sqrtf(aVal); }
inline float SC_InvSqrt(float aVal)			{ return 1.0f / sqrtf(aVal); }
inline float SC_Square(float aVal)			{ return aVal * aVal; }
inline float SC_Log(float aVal)				{ return logf(aVal); }
inline float SC_Log2(float aVal)			{ return log2f(aVal); }
inline float SC_Pow(float aVal, float aExp)	{ return powf(aVal, aExp); }
inline float SC_Exp(float aVal)				{ return expf(aVal); }
inline float SC_Exp2(float aVal)			{ return exp2f(aVal); }
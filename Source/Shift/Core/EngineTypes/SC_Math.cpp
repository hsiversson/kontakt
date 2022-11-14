//ProjectFilter(Math)
#include "EngineTypes_Precompiled.h"
#include "SC_Math.h"

#include <cmath>
#include <cfloat>

float SC_Abs(float aVal) 
{ 
	return fabsf(aVal); 
}
float SC_Floor(float aVal) 
{ 
	return floorf(aVal); 
}
float SC_Ceil(float aVal) 
{ 
	return ceilf(aVal);
}

float SC_Round(float aVal) 
{ 
	return roundf(aVal);
}

float SC_Frac(float aVal) 
{ 
	float intPart = 0; 
	return modf(aVal, &intPart); 
}

float SC_Sin(float aVal) 
{ 
	return sinf(aVal); 
}

float SC_Asin(float aVal) 
{ 
	return asinf(aVal);
}

float SC_Cos(float aVal) 
{ 
	return cosf(aVal);
}

float SC_Acos(float aVal) 
{ 
	return acosf(aVal);
}

void SC_SinCos(float& aOutSin, float& aOutCos, float aValue)
{
	aOutSin = sinf(aValue);
	aOutCos = cosf(aValue);
}

float SC_Tan(float aVal) 
{ 
	return tanf(aVal);
}

float SC_Atan(float aVal) 
{ 
	return atanf(aVal);
}

float SC_Atan2(float aY, float aX) 
{ 
	return atan2f(aY, aX);
}

float SC_Sqrt(float aVal) 
{ 
	return sqrtf(aVal);
}

float SC_InvSqrt(float aVal) 
{ 
	return 1.0f / sqrtf(aVal);
}

float SC_Square(float aVal) 
{ 
	return aVal * aVal;
}

float SC_Log(float aVal) 
{ 
	return logf(aVal);
}

float SC_Log2(float aVal) 
{ 
	return log2f(aVal);
}

float SC_Pow(float aVal, float aExp) 
{ 
	return powf(aVal, aExp);
}

float SC_Exp(float aVal) 
{ 
	return expf(aVal);
}

float SC_Exp2(float aVal) 
{ 
	return exp2f(aVal);
}
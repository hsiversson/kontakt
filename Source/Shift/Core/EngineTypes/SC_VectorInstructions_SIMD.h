//ProjectFilter(Math)
#pragma once
#ifndef __SC_VECTORINSTRUCTIONS_HEADER__
#error Please include SC_VectorInstructions.h instead.
#endif

#include "SC_TypeTraits.h"

#include <immintrin.h> // AVX2 requirement

namespace SC_VectorInstructions
{
	namespace Float
	{
		using Register = __m128;
		inline Register Load(float aValue)
		{
			return _mm_setr_ps(aValue, aValue, aValue, aValue);
		}

		inline Register Load(float aX, float aY, float aZ, float aW)
		{
			return _mm_setr_ps(aX, aY, aZ, aW);
		}

		inline void GetVector(Register aVec, float& aOutX, float& aOutY, float& aOutZ, float& aOutW)
		{
			aOutX = (((float*)&(aVec))[0]);
			aOutY = (((float*)&(aVec))[1]);
			aOutZ = (((float*)&(aVec))[2]);
			aOutW = (((float*)&(aVec))[3]);
		}

		inline Register Add(const Register& aVec1, const Register& aVec2)
		{
			return _mm_add_ps(aVec1, aVec2);
		}

		inline Register Subtract(const Register& aVec1, const Register& aVec2)
		{
			return _mm_sub_ps(aVec1, aVec2);
		}

		inline Register Multiply(const Register& aVec1, const Register& aVec2)
		{
			return _mm_mul_ps(aVec1, aVec2);
		}

		inline Register Divide(const Register& aVec1, const Register& aVec2)
		{
			return _mm_div_ps(aVec1, aVec2);
		}

		inline Register MultiplyAdd(const Register& aVec1, const Register& aVec2, const Register& aVec3)
		{
			return _mm_add_ps(_mm_mul_ps(aVec1, aVec2), aVec3);
		}
		
		inline Register Reciprocal(const Register& aVec)
		{
			return _mm_rcp_ps(aVec);
		}

		inline Register ReciprocalSqrt(const Register& aVec)
		{
			return _mm_rsqrt_ps(aVec);
		}

		inline Register Min(const Register& aVec1, const Register& aVec2)
		{
			return _mm_min_ps(aVec1, aVec2);
		}

		inline Register Max(const Register& aVec1, const Register& aVec2)
		{
			return _mm_max_ps(aVec1, aVec2);
		}

		inline Register Normalize(const Register& aVec)
		{
			return _mm_div_ps(aVec, _mm_sqrt_ps(_mm_dp_ps(aVec, aVec, 0xFF)));
		}

		inline Register Length(const Register& aVec)
		{

		}

		inline Register Dot(const Register& aVec0, const Register& aVec1)
		{
			return _mm_dp_ps(aVec0, aVec1, 0xFF);
		}
	}

	namespace Int
	{
		using Register = __m128i;
		inline Register Load(int aValue)
		{
			return _mm_setr_epi32(aValue, aValue, aValue, aValue);
		}

		inline Register Load(int aX, int aY, int aZ, int aW)
		{
			return _mm_setr_epi32(aX, aY, aZ, aW);
		}

		inline void GetVector(Register aVec, int& aOutX, int& aOutY, int& aOutZ, int& aOutW)
		{
			aOutX = (((float*)&(aVec))[0]);
			aOutY = (((float*)&(aVec))[1]);
			aOutZ = (((float*)&(aVec))[2]);
			aOutW = (((float*)&(aVec))[3]);
		}

		inline Register Add(const Register& aVec1, const Register& aVec2)
		{
			return _mm_add_epi32(aVec1, aVec2);
		}

		inline Register Subtract(const Register& aVec1, const Register& aVec2)
		{
			return _mm_sub_epi32(aVec1, aVec2);
		}

		inline Register Multiply(const Register& aVec1, const Register& aVec2)
		{
			return _mm_mul_epi32(aVec1, aVec2);
		}

		inline Register Divide(const Register& aVec1, const Register& aVec2)
		{
			return _mm_div_epi32(aVec1, aVec2);
		}

		inline Register MultiplyAdd(const Register& aVec1, const Register& aVec2, const Register& aVec3)
		{
			return _mm_add_epi32(_mm_mul_epi32(aVec1, aVec2), aVec3);
		}

		inline Register Reciprocal(const Register& aVec)
		{
			return aVec;
		}

		inline Register ReciprocalSqrt(const Register& aVec)
		{
			return aVec;
		}

		inline Register Min(const Register& aVec1, const Register& aVec2)
		{
			return _mm_min_epi32(aVec1, aVec2);
		}

		inline Register Max(const Register& aVec1, const Register& aVec2)
		{
			return _mm_min_epi32(aVec1, aVec2);
		}
	}
}
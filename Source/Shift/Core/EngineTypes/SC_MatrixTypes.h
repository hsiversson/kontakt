//ProjectFilter(Math)
#pragma once
#include "SC_Matrix.h"

class SC_ScaleMatrix : public SC_Matrix
{
public:
	SC_ScaleMatrix(float aScale)
		: SC_Matrix(
			SC_Vector4(aScale, 0.0f, 0.0f, 0.0f),
			SC_Vector4(0.0f, aScale, 0.0f, 0.0f),
			SC_Vector4(0.0f, 0.0f, aScale, 0.0f),
			SC_Vector4(0.0f, 0.0f, 0.0f, 1.0f))
	{}

	SC_ScaleMatrix(const SC_Vector& aScale)
		: SC_Matrix(
			SC_Vector4(aScale.x, 0.0f, 0.0f, 0.0f),
			SC_Vector4(0.0f, aScale.y, 0.0f, 0.0f),
			SC_Vector4(0.0f, 0.0f, aScale.z, 0.0f),
			SC_Vector4(0.0f, 0.0f, 0.0f, 1.0f))
	{}
};

class SC_TranslationMatrix : public SC_Matrix
{
public:
	SC_TranslationMatrix(const SC_Vector& aPosition)
		: SC_Matrix(
			SC_Vector4(1.0f, 0.0f, 0.0f, 0.0f),
			SC_Vector4(0.0f, 1.0f, 0.0f, 0.0f),
			SC_Vector4(0.0f, 0.0f, 1.0f, 0.0f),
			SC_Vector4(aPosition.x, aPosition.y, aPosition.z, 1.0f))
	{}
};

class SC_PerspectiveMatrix : public SC_Matrix
{
public:
	SC_PerspectiveMatrix(float aHalfFOV, float aWidth, float aHeight, float aMinZ, float aMaxZ)
		: SC_Matrix(
			SC_Vector4(1.0f / SC_Tan(aHalfFOV), 0.0f, 0.0f, 0.0f),
			SC_Vector4(0.0f, aWidth / SC_Tan(aHalfFOV) / aHeight, 0.0f, 0.0f),
			SC_Vector4(0.0f, 0.0f, ((aMinZ == aMaxZ) ? (1.0f) : aMaxZ / (aMaxZ - aMinZ)), 1.0f),
			SC_Vector4(0.0f, 0.0f, -aMinZ * ((aMinZ == aMaxZ) ? (1.0f) : aMaxZ / (aMaxZ - aMinZ)), 0.0f))
	{}
};

class SC_PerspectiveInvZMatrix : public SC_Matrix
{
public:
	SC_PerspectiveInvZMatrix(float aHalfFOV, float aWidth, float aHeight, float aMinZ, float aMaxZ)
		: SC_Matrix(
			SC_Vector4(1.0f / SC_Tan(aHalfFOV), 0.0f, 0.0f, 0.0f),
			SC_Vector4(0.0f, aWidth / SC_Tan(aHalfFOV) / aHeight, 0.0f, 0.0f),
			SC_Vector4(0.0f, 0.0f, ((aMinZ == aMaxZ) ? 0.0f : aMinZ / (aMinZ - aMaxZ)), 1.0f),
			SC_Vector4(0.0f, 0.0f, ((aMinZ == aMaxZ) ? aMinZ : -aMaxZ * aMinZ / (aMinZ - aMaxZ)), 0.0f))
	{}
};

class SC_OrthogonalMatrix : public SC_Matrix
{
public:
	SC_OrthogonalMatrix(float aWidth, float aHeight, float aZScale, float aZOffset)
		: SC_Matrix(
			SC_Vector4((aWidth != 0.0f) ? (1.0f / aWidth) : 1.0f, 0.0f, 0.0f, 0.0f),
			SC_Vector4(0.0f, (aHeight != 0.0f) ? (1.0f / aHeight) : 1.f, 0.0f, 0.0f),
			SC_Vector4(0.0f, 0.0f, aZScale, 0.0f),
			SC_Vector4(0.0f, 0.0f, aZOffset* aZScale, 1.0f))
	{}
};

class SC_OrthogonalInvZMatrix : public SC_Matrix
{
public:
	SC_OrthogonalInvZMatrix(float aWidth, float aHeight, float aZScale, float aZOffset)
		: SC_Matrix(
			SC_Vector4((aWidth != 0.0f) ? (1.0f / aWidth) : 1.0f, 0.0f, 0.0f, 0.0f),
			SC_Vector4(0.0f, (aHeight != 0.0f) ? (1.0f / aHeight) : 1.f, 0.0f, 0.0f),
			SC_Vector4(0.0f, 0.0f, -aZScale, 0.0f),
			SC_Vector4(0.0f, 0.0f, 1.0f - aZOffset * aZScale, 1.0f))
	{}
};

class SC_LookAtMatrix : public SC_Matrix
{
public:
	SC_LookAtMatrix(const SC_Vector& aFromPosition, const SC_Vector& aLookAtPosition, const SC_Vector& aUpVector)
	{
		const SC_Vector zAxis = (aLookAtPosition - aFromPosition).GetNormalized();
		const SC_Vector xAxis = aUpVector.Cross(zAxis).GetNormalized();
		const SC_Vector yAxis = zAxis.Cross(xAxis);

		for (uint32 row = 0; row < 3; row++)
		{
			uint32 offset = 4 * row;

			mData[0 + offset] = (&xAxis.x)[row];
			mData[1 + offset] = (&yAxis.x)[row];
			mData[2 + offset] = (&zAxis.x)[row];
			mData[3 + offset] = 0.0f;
		}


		uint32 offset = 4 * 3;
		mData[0 + offset] = -aFromPosition.Dot(xAxis);
		mData[1 + offset] = -aFromPosition.Dot(yAxis);
		mData[2 + offset] = -aFromPosition.Dot(zAxis);
		mData[3 + offset] = 1.0f;
	}
};
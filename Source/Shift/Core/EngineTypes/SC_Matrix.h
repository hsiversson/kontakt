//ProjectFilter(Math)
#pragma once
#define __SC_MATRIX_HEADER__

#include "SC_Vector.h"

class SC_Matrix33;
class SC_Matrix44;

#include "SC_Matrix33.h"
#include "SC_Matrix44.h"
#include "SC_MatrixTypes.h"

inline SC_Vector operator*(const SC_Vector& aVector, const SC_Matrix& aMatrix)
{
	const SC_Vector4 xAxis = aMatrix.mAxisX;
	const SC_Vector4 yAxis = aMatrix.mAxisY;
	const SC_Vector4 zAxis = aMatrix.mAxisZ;
	const SC_Vector4 translation = aMatrix.GetTranslation();
	return SC_Vector(
		(aVector.x * xAxis.x + aVector.y * yAxis.x + aVector.z * zAxis.x + translation.x),
		(aVector.x * xAxis.y + aVector.y * yAxis.y + aVector.z * zAxis.y + translation.y),
		(aVector.x * xAxis.z + aVector.y * yAxis.z + aVector.z * zAxis.z + translation.z));
}

inline SC_Vector& operator*=(SC_Vector& aVector, const SC_Matrix& aMatrix)
{
	aVector = aVector * aMatrix;
	return aVector;
}

inline SC_Vector4 operator*(const SC_Vector4& aVector, const SC_Matrix& aMatrix)
{
	return SC_Vector4(
		(aVector.x * aMatrix.mData[0] + aVector.y * aMatrix.mData[4] + aVector.z * aMatrix.mData[8] + aVector.w * aMatrix.mData[12]),
		(aVector.x * aMatrix.mData[1] + aVector.y * aMatrix.mData[5] + aVector.z * aMatrix.mData[9] + aVector.w * aMatrix.mData[13]),
		(aVector.x * aMatrix.mData[2] + aVector.y * aMatrix.mData[6] + aVector.z * aMatrix.mData[10] + aVector.w * aMatrix.mData[14]),
		(aVector.x * aMatrix.mData[3] + aVector.y * aMatrix.mData[7] + aVector.z * aMatrix.mData[11] + aVector.w * aMatrix.mData[15]));
}

inline SC_Vector4& operator*=(SC_Vector4& aVector, const SC_Matrix& aMatrix)
{
	aVector = aVector * aMatrix;
	return aVector;
}
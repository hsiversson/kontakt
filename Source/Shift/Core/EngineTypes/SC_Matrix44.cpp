//ProjectFilter(Math)
#include "EngineTypes_Precompiled.h"
#include "SC_Matrix44.h"

const SC_Matrix44 SC_Matrix44::gIdentity = SC_Matrix44(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
const SC_Matrix44 SC_Matrix44::gZero = SC_Matrix44(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);

SC_Matrix44::SC_Matrix44()
{
}

SC_Matrix44::SC_Matrix44(const SC_Matrix44& aMatrix)
	: mAxisX(aMatrix.mAxisX)
	, mAxisY(aMatrix.mAxisY)
	, mAxisZ(aMatrix.mAxisZ)
	, mAxisW(aMatrix.mAxisW)
{
}

SC_Matrix44::SC_Matrix44(const SC_Vector4& aXAxis, const SC_Vector4& aYAxis, const SC_Vector4& aZAxis, const SC_Vector4& aTranslation)
	: mAxisX(aXAxis)
	, mAxisY(aYAxis)
	, mAxisZ(aZAxis)
	, mAxisW(aTranslation)
{
}

SC_Matrix44::SC_Matrix44(float M00, float M01, float M02, float M03, float M10, float M11, float M12, float M13, float M20, float M21, float M22, float M23, float M30, float M31, float M32, float M33)
	: mAxisX(SC_Vector4(M00, M01, M02, M03))
	, mAxisY(SC_Vector4(M10, M11, M12, M13))
	, mAxisZ(SC_Vector4(M20, M21, M22, M23))
	, mAxisW(SC_Vector4(M30, M31, M32, M33))
{
}

inline float SC_Matrix44::At(uint32 aRow, uint32 aCol) const
{
	return mData44[aRow][aCol];
}

inline void SC_Matrix44::Set(uint32 aRow, uint32 aCol, float aValue)
{
	mData44[aRow][aCol] = aValue;
}

inline const SC_Matrix44& SC_Matrix44::Transpose()
{
	*this = SC_Matrix44(mData[0], mData[4], mData[8], mData[12],
		mData[1], mData[5], mData[9], mData[13],
		mData[2], mData[6], mData[10], mData[14],
		mData[3], mData[7], mData[11], mData[15]);
	return *this;

}

inline const SC_Matrix44& SC_Matrix44::FastInvert()
{
	float scaleX = mAxisX.XYZ().Length2();
	float scaleY = mAxisY.XYZ().Length2();
	float scaleZ = mAxisZ.XYZ().Length2();
	if ((scaleX > 0.0000001f) && (scaleY > 0.0000001f) && (scaleZ > 0.0000001f) && (mAxisW.w == 1.0f))
	{
		scaleX = 1.0f / scaleX;
		scaleY = 1.0f / scaleY;
		scaleZ = 1.0f / scaleZ;

		SC_Vector4 axisX(mAxisX.x * scaleX, mAxisY.x * scaleY, mAxisZ.x * scaleZ, 0.0f);
		SC_Vector4 axisY(mAxisX.y * scaleX, mAxisY.y * scaleY, mAxisZ.y * scaleZ, 0.0f);
		SC_Vector4 axisZ(mAxisX.z * scaleX, mAxisY.z * scaleY, mAxisZ.z * scaleZ, 0.0f);
		SC_Vector4 axisW(
			-(mAxisW.x * mAxisX.x + mAxisW.y * mAxisX.y + mAxisW.z * mAxisX.z) * scaleX,
			-(mAxisW.x * mAxisY.x + mAxisW.y * mAxisY.y + mAxisW.z * mAxisY.z) * scaleY,
			-(mAxisW.x * mAxisZ.x + mAxisW.y * mAxisZ.y + mAxisW.z * mAxisZ.z) * scaleZ,
			1.0f);

		*this = SC_Matrix44(axisX, axisY, axisZ, axisW);
	}

	return *this;
}

inline const SC_Matrix44& SC_Matrix44::Invert()
{
	float inv[16];
	float m[16];
	float det;

	for (int j = 0; j < 4; ++j)
	{
		for (int k = 0; k < 4; ++k)
			m[j * 4 + k] = mData44[j][k];
	}

	inv[0] = m[5] * m[10] * m[15] -
		m[5] * m[11] * m[14] -
		m[9] * m[6] * m[15] +
		m[9] * m[7] * m[14] +
		m[13] * m[6] * m[11] -
		m[13] * m[7] * m[10];

	inv[4] = -m[4] * m[10] * m[15] +
		m[4] * m[11] * m[14] +
		m[8] * m[6] * m[15] -
		m[8] * m[7] * m[14] -
		m[12] * m[6] * m[11] +
		m[12] * m[7] * m[10];

	inv[8] = m[4] * m[9] * m[15] -
		m[4] * m[11] * m[13] -
		m[8] * m[5] * m[15] +
		m[8] * m[7] * m[13] +
		m[12] * m[5] * m[11] -
		m[12] * m[7] * m[9];

	inv[12] = -m[4] * m[9] * m[14] +
		m[4] * m[10] * m[13] +
		m[8] * m[5] * m[14] -
		m[8] * m[6] * m[13] -
		m[12] * m[5] * m[10] +
		m[12] * m[6] * m[9];

	inv[1] = -m[1] * m[10] * m[15] +
		m[1] * m[11] * m[14] +
		m[9] * m[2] * m[15] -
		m[9] * m[3] * m[14] -
		m[13] * m[2] * m[11] +
		m[13] * m[3] * m[10];

	inv[5] = m[0] * m[10] * m[15] -
		m[0] * m[11] * m[14] -
		m[8] * m[2] * m[15] +
		m[8] * m[3] * m[14] +
		m[12] * m[2] * m[11] -
		m[12] * m[3] * m[10];

	inv[9] = -m[0] * m[9] * m[15] +
		m[0] * m[11] * m[13] +
		m[8] * m[1] * m[15] -
		m[8] * m[3] * m[13] -
		m[12] * m[1] * m[11] +
		m[12] * m[3] * m[9];

	inv[13] = m[0] * m[9] * m[14] -
		m[0] * m[10] * m[13] -
		m[8] * m[1] * m[14] +
		m[8] * m[2] * m[13] +
		m[12] * m[1] * m[10] -
		m[12] * m[2] * m[9];

	inv[2] = m[1] * m[6] * m[15] -
		m[1] * m[7] * m[14] -
		m[5] * m[2] * m[15] +
		m[5] * m[3] * m[14] +
		m[13] * m[2] * m[7] -
		m[13] * m[3] * m[6];

	inv[6] = -m[0] * m[6] * m[15] +
		m[0] * m[7] * m[14] +
		m[4] * m[2] * m[15] -
		m[4] * m[3] * m[14] -
		m[12] * m[2] * m[7] +
		m[12] * m[3] * m[6];

	inv[10] = m[0] * m[5] * m[15] -
		m[0] * m[7] * m[13] -
		m[4] * m[1] * m[15] +
		m[4] * m[3] * m[13] +
		m[12] * m[1] * m[7] -
		m[12] * m[3] * m[5];

	inv[14] = -m[0] * m[5] * m[14] +
		m[0] * m[6] * m[13] +
		m[4] * m[1] * m[14] -
		m[4] * m[2] * m[13] -
		m[12] * m[1] * m[6] +
		m[12] * m[2] * m[5];

	inv[3] = -m[1] * m[6] * m[11] +
		m[1] * m[7] * m[10] +
		m[5] * m[2] * m[11] -
		m[5] * m[3] * m[10] -
		m[9] * m[2] * m[7] +
		m[9] * m[3] * m[6];

	inv[7] = m[0] * m[6] * m[11] -
		m[0] * m[7] * m[10] -
		m[4] * m[2] * m[11] +
		m[4] * m[3] * m[10] +
		m[8] * m[2] * m[7] -
		m[8] * m[3] * m[6];

	inv[11] = -m[0] * m[5] * m[11] +
		m[0] * m[7] * m[9] +
		m[4] * m[1] * m[11] -
		m[4] * m[3] * m[9] -
		m[8] * m[1] * m[7] +
		m[8] * m[3] * m[5];

	inv[15] = m[0] * m[5] * m[10] -
		m[0] * m[6] * m[9] -
		m[4] * m[1] * m[10] +
		m[4] * m[2] * m[9] +
		m[8] * m[1] * m[6] -
		m[8] * m[2] * m[5];

	det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];

	if (det > 0)
	{
		det = 1.0f / det;
		for (int j = 0; j < 4; ++j)
		{
			for (int k = 0; k < 4; ++k)
				mData44[j][k] = inv[j * 4 + k] * det;
		}
	}
	return *this;
}

SC_Matrix44 SC_Matrix44::GetTransposed() const
{
	SC_Matrix44 transposed = *this;
	return transposed.Transpose();
}

SC_Matrix44 SC_Matrix44::GetFastInversed() const
{
	SC_Matrix44 inversed = *this;
	return inversed.FastInvert();
}

SC_Matrix44 SC_Matrix44::GetInversed() const
{
	SC_Matrix44 inversed = *this;
	return inversed.Invert();
}

SC_Vector4 SC_Matrix44::GetTranslation() const
{
	return mAxisW;
}

SC_Vector SC_Matrix44::GetPosition() const
{
	return mAxisW.XYZ();
}

SC_Vector SC_Matrix44::GetScale() const
{
	SC_Vector scale;
	scale.x = mAxisX.Length();
	scale.y = mAxisY.Length();
	scale.z = mAxisZ.Length();
	return scale;
}

SC_Vector SC_Matrix44::GetRight() const
{
	SC_Vector right = mAxisX.XYZ();
	return right.GetNormalized();
}

SC_Vector SC_Matrix44::GetUp() const
{
	SC_Vector up = mAxisY.XYZ();
	return up.GetNormalized();
}

SC_Vector SC_Matrix44::GetForward() const
{
	SC_Vector forward = mAxisZ.XYZ();
	return forward.GetNormalized();
}

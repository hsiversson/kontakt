//ProjectFilter(Math)
#pragma once
#include "SC_Vector.h"

class alignas(16) SC_Matrix44
{
public:
	union
	{
		float mData[16];
		float mData44[4][4];
		struct
		{
			SC_Vector4 mAxisX;
			SC_Vector4 mAxisY;
			SC_Vector4 mAxisZ;
			SC_Vector4 mAxisW;
		};
	};

	static const SC_Matrix44 gIdentity;
	static const SC_Matrix44 gZero;

public:
	SC_Matrix44();
	SC_Matrix44(const SC_Matrix44& aMatrix);
	SC_Matrix44(const SC_Vector4& aXAxis, const SC_Vector4& aYAxis, const SC_Vector4& aZAxis, const SC_Vector4& aTranslation);
	SC_Matrix44(float M00, float M01, float M02, float M03,
			  float M10, float M11, float M12, float M13,
			  float M20, float M21, float M22, float M23,
			  float M30, float M31, float M32, float M33);

	float At(uint32 aRow, uint32 aCol) const;
	void Set(uint32 aRow, uint32 aCol, float aValue);

	const SC_Matrix44& Transpose();
	const SC_Matrix44& FastInvert();
	const SC_Matrix44& Invert();

	SC_Matrix44 GetTransposed() const;
	SC_Matrix44 GetFastInversed() const;
	SC_Matrix44 GetInversed() const;

	SC_Vector4 GetTranslation() const;
	SC_Vector GetPosition() const;
	SC_Vector GetScale() const;

	SC_Vector GetRight() const;
	SC_Vector GetUp() const;
	SC_Vector GetForward() const;
};

using SC_Matrix = SC_Matrix44;
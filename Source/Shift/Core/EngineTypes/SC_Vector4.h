//ProjectFilter(Math)
#pragma once

#ifndef __SC_VECTOR_HEADER__
#error Please include SC_Vector.h instead.
#endif

template<class T>
class SC_TVector4
{
public:
	union
	{
		struct  {T x, y, z, w; };
		T mData[4];
	};

	//static const SC_TVector4<T> gZeroVector = SC_TVector4<T>(static_cast<T>(0));
	//static const SC_TVector4<T> gOneVector = SC_TVector4<T>(static_cast<T>(1));
public:
	SC_TVector4();
	SC_TVector4(T aScalar);
	SC_TVector4(T aX, T aY, T aZ, T aW);
	SC_TVector4(const SC_TVector2<T>& aVec0, const SC_TVector2<T>& aVec1);
	SC_TVector4(const SC_TVector3<T>& aVec, T aW = 1.0f);
	SC_TVector4(const SC_TVector4& aVec);

	void Normalize();
	SC_TVector4 GetNormalized() const;

	T Length() const;
	T Length2() const;

	T Dot(const SC_TVector4& aVec);
	T Cross(const SC_TVector4& aVec);

	// Swizzles
	SC_TVector2<T> XY() const { return SC_TVector2<T>(x, y); }
	SC_TVector2<T> XX() const { return SC_TVector2<T>(x, x); }
	SC_TVector2<T> YX() const { return SC_TVector2<T>(y, x); }
	SC_TVector2<T> YY() const { return SC_TVector2<T>(y, y); }

	SC_TVector3<T> XXX() const { return SC_TVector3<T>(x, x, x); }
	SC_TVector3<T> XYX() const { return SC_TVector3<T>(x, y, x); }
	SC_TVector3<T> XZX() const { return SC_TVector3<T>(x, z, x); }
	SC_TVector3<T> XYY() const { return SC_TVector3<T>(x, y, y); }
	SC_TVector3<T> XZZ() const { return SC_TVector3<T>(x, z, z); }
	SC_TVector3<T> YYY() const { return SC_TVector3<T>(y, y, y); }
	SC_TVector3<T> ZZZ() const { return SC_TVector3<T>(z, z, z); }
	SC_TVector3<T> YYX() const { return SC_TVector3<T>(y, y, x); }
	SC_TVector3<T> YXX() const { return SC_TVector3<T>(y, x, x); }
	SC_TVector3<T> XYZ() const { return SC_TVector3<T>(x, y, z); }

	//Negate operator
	SC_TVector4 operator-() const;

	// Subtraction operators
	SC_TVector4& operator-=(const SC_TVector4& aVector);
	SC_TVector4& operator-=(const float& aValue);
	SC_TVector4 operator-(const SC_TVector4& aVector) const;
	SC_TVector4 operator-(const float& aValue) const;

	//Multiplication operators
	SC_TVector4& operator*=(const SC_TVector4& aVector);
	SC_TVector4& operator*=(const float& aValue);
	SC_TVector4 operator*(const SC_TVector4& aVector) const;
	SC_TVector4 operator*(const float& aValue) const;

	//Addition operators
	SC_TVector4& operator+=(const SC_TVector4& aVector);
	SC_TVector4& operator+=(const float& aValue);
	SC_TVector4 operator+(const SC_TVector4& aVector) const;
	SC_TVector4 operator+(const float& aValue) const;

	//Division operators
	SC_TVector4& operator/=(const SC_TVector4& aVector);
	SC_TVector4& operator/=(const float& aValue);
	SC_TVector4 operator/(const SC_TVector4& aVector) const;
	SC_TVector4 operator/(const float& aValue) const;

};

template<class T>
inline SC_TVector4<T>::SC_TVector4()
	: x(static_cast<T>(0)), y(static_cast<T>(0)), z(static_cast<T>(0)), w(static_cast<T>(0))
{
}

template<class T>
inline SC_TVector4<T>::SC_TVector4(T aScalar)
	: x(aScalar), y(aScalar), z(aScalar), w(aScalar)
{
}

template<class T>
inline SC_TVector4<T>::SC_TVector4(T aX, T aY, T aZ, T aW)
	: x(aX), y(aY), z(aZ), w(aW)
{
}

template<class T>
inline SC_TVector4<T>::SC_TVector4(const SC_TVector2<T>& aVec0, const SC_TVector2<T>& aVec1)
	: x(aVec0.x), y(aVec0.y), z(aVec1.x), w(aVec1.y)
{
}

template<class T>
inline SC_TVector4<T>::SC_TVector4(const SC_TVector3<T>& aVec, T aW)
	: x(aVec.x), y(aVec.y), z(aVec.z), w(aW)
{
}

template<class T>
inline SC_TVector4<T>::SC_TVector4(const SC_TVector4& aVec)
	: x(aVec.x), y(aVec.y), z(aVec.z), w(aVec.w)
{
}

template<class T>
inline void SC_TVector4<T>::Normalize()
{
	const float l2 = x*x + y*y + z*z + w*w;
	if (l2 > 0.f)
	{
		const float scale = SC_InvSqrt(l2);
		x *= scale;
		y *= scale;
		z *= scale;
		w *= scale;
	}
}

template<class T>
inline SC_TVector4<T> SC_TVector4<T>::GetNormalized() const
{
	SC_TVector4 v(*this);
	return v.Normalize();
}

template<class T>
inline T SC_TVector4<T>::Length() const
{
	return SC_Sqrt(x*x + y*y + z*z + w*w);
}

template<class T>
inline T SC_TVector4<T>::Length2() const
{
	return (x*x + y*y + z*z + w*w);
}

template<class T>
inline T SC_TVector4<T>::Dot(const SC_TVector4& aVec)
{
	return x * aVec.x + y * aVec.y + z * aVec.z + w * aVec.w;
}

template<class T>
inline T SC_TVector4<T>::Cross(const SC_TVector4& aVec)
{
	return SC_TVector3<T>(
		(y * aVec.z - z * aVec.y),
		(z * aVec.x - x * aVec.z),
		(x * aVec.y - y * aVec.x),
		static_cast<T>(0));
}

template<class T>
inline SC_TVector4<T> SC_TVector4<T>::operator-() const
{
	return SC_TVector4(-x, -y, -z, -w);
}

template<class T>
inline SC_TVector4<T>& SC_TVector4<T>::operator-=(const SC_TVector4& aVector)
{
	x -= aVector.x;
	y -= aVector.y;
	z -= aVector.z;
	w -= aVector.w;
	return *this;
}

template<class T>
inline SC_TVector4<T>& SC_TVector4<T>::operator-=(const float& aValue)
{
	x -= aValue;
	y -= aValue;
	z -= aValue;
	w -= aValue;
	return *this;
}

template<class T>
inline SC_TVector4<T> SC_TVector4<T>::operator-(const SC_TVector4& aVector) const
{
	return SC_TVector4<T>(x - aVector.x, y - aVector.y, z - aVector.z, w - aVector.w);
}

template<class T>
inline SC_TVector4<T> SC_TVector4<T>::operator-(const float& aValue) const
{
	return SC_TVector4<T>(x - aValue, y - aValue, z - aValue, w - aValue);
}

template<class T>
inline SC_TVector4<T> operator-(const float& aValue, const SC_TVector4<T>& aVector)
{
	return SC_TVector4<T>(aValue - aVector.x, aValue - aVector.y, aValue - aVector.z, aValue - aVector.w);
}

template<class T>
inline SC_TVector4<T>& SC_TVector4<T>::operator*=(const SC_TVector4& aVector)
{
	x *= aVector.x;
	y *= aVector.y;
	z *= aVector.z;
	w *= aVector.w;
	return *this;
}

template<class T>
inline SC_TVector4<T>& SC_TVector4<T>::operator*=(const float& aValue)
{
	x *= aValue;
	y *= aValue;
	z *= aValue;
	w *= aValue;
	return *this;
}

template<class T>
inline SC_TVector4<T> SC_TVector4<T>::operator*(const SC_TVector4& aVector) const
{
	return SC_TVector4<T>(x * aVector.x, y * aVector.y, z * aVector.z, w * aVector.w);
}

template<class T>
inline SC_TVector4<T> SC_TVector4<T>::operator*(const float& aValue) const
{
	return SC_TVector4<T>(x * aValue, y * aValue, z * aValue, w * aValue);
}

template<class T>
inline SC_TVector4<T> operator*(const float& aValue, const SC_TVector4<T>& aVector)
{
	return SC_TVector4<T>(aValue * aVector.x, aValue * aVector.y, aValue * aVector.z, aValue * aVector.w);
}

template<class T>
inline SC_TVector4<T>& SC_TVector4<T>::operator+=(const SC_TVector4& aVector)
{
	x += aVector.x;
	y += aVector.y;
	z += aVector.z;
	w += aVector.w;
	return *this;
}

template<class T>
inline SC_TVector4<T>& SC_TVector4<T>::operator+=(const float& aValue)
{
	x += aValue;
	y += aValue;
	z += aValue;
	w += aValue;
	return *this;
}

template<class T>
inline SC_TVector4<T> SC_TVector4<T>::operator+(const SC_TVector4& aVector) const
{
	return SC_TVector4<T>(x + aVector.x, y + aVector.y, z + aVector.z, w + aVector.w);
}

template<class T>
inline SC_TVector4<T> SC_TVector4<T>::operator+(const float& aValue) const
{
	return SC_TVector4<T>(x + aValue, y +aValue, z + aValue, w + aValue);
}

template<class T>
inline SC_TVector4<T> operator+(const float& aValue, const SC_TVector4<T>& aVector)
{
	return SC_TVector4<T>(aValue + aVector.x, aValue + aVector.y, aValue + aVector.z, aValue + aVector.w);
}

template<class T>
inline SC_TVector4<T>& SC_TVector4<T>::operator/=(const SC_TVector4& aVector)
{
	x /= aVector.x;
	y /= aVector.y;
	z /= aVector.z;
	w /= aVector.w;
	return *this;
}

template<class T>
inline SC_TVector4<T>& SC_TVector4<T>::operator/=(const float& aValue)
{
	x /= aValue;
	y /= aValue;
	z /= aValue;
	w /= aValue;
	return *this;
}

template<class T>
inline SC_TVector4<T> SC_TVector4<T>::operator/(const SC_TVector4& aVector) const
{
	return SC_TVector4<T>(x / aVector.x, y / aVector.y, z / aVector.z, w / aVector.w);
}

template<class T>
inline SC_TVector4<T> SC_TVector4<T>::operator/(const float& aValue) const
{
	return SC_TVector4<T>(x / aValue, y / aValue, z / aValue, w / aValue);
}

template<class T>
inline SC_TVector4<T> operator/(const float& aValue, const SC_TVector4<T>& aVector)
{
	return SC_TVector4<T>(aValue / aVector.x, aValue / aVector.y, aValue / aVector.z, aValue / aVector.w);
}

using SC_Vector4 = SC_TVector4<float>;
using SC_Vector4d = SC_TVector4<double>;
using SC_Vector4i = SC_TVector4<int32>;
using SC_Vector4ui = SC_TVector4<uint32>;
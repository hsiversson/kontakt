//ProjectFilter(Math)
#pragma once

#ifndef __SC_VECTOR_HEADER__
#error Please include SC_Vector.h instead.
#endif

template<class T>
class SC_TVector3
{
public:
	union
	{
		struct { T x, y, z;	};
		T mData[3];
	};

	static const SC_TVector3 gZeroVector;
	static const SC_TVector3 gOneVector;

	static const SC_TVector3 gLeftVector;
	static const SC_TVector3 gRightVector;
	static const SC_TVector3 gUpVector;
	static const SC_TVector3 gDownVector;
	static const SC_TVector3 gForwardVector;
	static const SC_TVector3 gBackwardVector;

public:
	SC_TVector3();
	SC_TVector3(T aScalar);
	SC_TVector3(T aX, T aY, T aZ);
	SC_TVector3(const SC_TVector2<T>& aVec, T aZ = static_cast<T>(0));
	SC_TVector3(const SC_TVector3& aVec);

	void Normalize();
	SC_TVector3 GetNormalized() const;

	T Length() const;
	T Length2() const;

	T Dot(const SC_TVector3& aVec);
	T Cross(const SC_TVector3& aVec);

	// Swizzles
	SC_TVector2<T> XY() const { return SC_TVector2<T>(x, y); }
	SC_TVector2<T> XX() const { return SC_TVector2<T>(x, x); }
	SC_TVector2<T> YX() const { return SC_TVector2<T>(y, x); }
	SC_TVector2<T> YY() const { return SC_TVector2<T>(y, y); }

	SC_TVector3 XXX() const { return SC_TVector3(x, x, x); }
	SC_TVector3 XYX() const { return SC_TVector3(x, y, x); }
	SC_TVector3 XZX() const { return SC_TVector3(x, z, x); }
	SC_TVector3 XYY() const { return SC_TVector3(x, y, y); }
	SC_TVector3 XZZ() const { return SC_TVector3(x, z, z); }
	SC_TVector3 YYY() const { return SC_TVector3(y, y, y); }
	SC_TVector3 ZZZ() const { return SC_TVector3(z, z, z); }
	SC_TVector3 YYX() const { return SC_TVector3(y, y, x); }
	SC_TVector3 YXX() const { return SC_TVector3(y, x, x); }

	//Negate operator
	SC_TVector3 operator-() const;

	// Subtraction operators
	SC_TVector3& operator-=(const SC_TVector3& aVector);
	SC_TVector3& operator-=(const T& aValue);
	SC_TVector3 operator-(const SC_TVector3& aVector) const;
	SC_TVector3 operator-(const T& aValue) const;

	//Multiplication operators
	SC_TVector3& operator*=(const SC_TVector3& aVector);
	SC_TVector3& operator*=(const T& aValue);
	SC_TVector3 operator*(const SC_TVector3& aVector) const;
	SC_TVector3 operator*(const T& aValue) const;

	//Addition operators
	SC_TVector3& operator+=(const SC_TVector3& aVector);
	SC_TVector3& operator+=(const T& aValue);
	SC_TVector3 operator+(const SC_TVector3& aVector) const;
	SC_TVector3 operator+(const T& aValue) const;

	//Division operators
	SC_TVector3& operator/=(const SC_TVector3& aVector);
	SC_TVector3& operator/=(const T& aValue);
	SC_TVector3 operator/(const SC_TVector3& aVector) const;
	SC_TVector3 operator/(const T& aValue) const;
};

template<class T>
inline SC_TVector3<T>::SC_TVector3()
	: x(static_cast<T>(0)), y(static_cast<T>(0)), z(static_cast<T>(0))
{
}

template<class T>
inline SC_TVector3<T>::SC_TVector3(T aScalar)
	: x(aScalar), y(aScalar), z(aScalar)
{
}

template<class T>
inline SC_TVector3<T>::SC_TVector3(T aX, T aY, T aZ)
	: x(aX), y(aY), z(aZ)
{
}

template<class T>
inline SC_TVector3<T>::SC_TVector3(const SC_TVector2<T>& aVec, T aZ)
	: x(aVec.x), y(aVec.y), z(aZ)
{
}

template<class T>
inline SC_TVector3<T>::SC_TVector3(const SC_TVector3& aVec)
	: x(aVec.x), y(aVec.y), z(aVec.z)
{
}

template<class T>
inline void SC_TVector3<T>::Normalize()
{
	const float l2 = x*x + y*y + z*z;
	if (l2 > 0.f)
	{
		const float scale = SC_InvSqrt(l2);
		x *= scale;
		y *= scale;
		z *= scale;
	}
}

template<class T>
inline SC_TVector3<T> SC_TVector3<T>::GetNormalized() const
{
	SC_TVector3 v(*this);
	v.Normalize();
	return v;
}

template<class T>
inline T SC_TVector3<T>::Length() const
{
	return SC_Sqrt(x*x + y*y + z*z);
}

template<class T>
inline T SC_TVector3<T>::Length2() const
{
	return (x*x + y*y + z*z);
}

template<class T>
inline T SC_TVector3<T>::Dot(const SC_TVector3& aVec)
{
	return x * aVec.x + y * aVec.y + z * aVec.z;
}

template<class T>
inline T SC_TVector3<T>::Cross(const SC_TVector3& aVec)
{
	return SC_TVector3<T>(
		(y * aVec.z - z * aVec.y),
		(z * aVec.x - x * aVec.z),
		(x * aVec.y - y * aVec.x));
}

template<class T>
inline SC_TVector3<T> SC_TVector3<T>::operator-() const
{
	return SC_TVector3(-x, -y, -z);
}

template<class T>
inline SC_TVector3<T>& SC_TVector3<T>::operator-=(const SC_TVector3& aVector)
{
	x -= aVector.x;
	y -= aVector.y;
	z -= aVector.z;
	return *this;
}

template<class T>
inline SC_TVector3<T>& SC_TVector3<T>::operator-=(const T& aValue)
{
	x -= aValue;
	y -= aValue;
	z -= aValue;
	return *this;
}

template<class T>
inline SC_TVector3<T> SC_TVector3<T>::operator-(const SC_TVector3& aVector) const
{
	return SC_TVector3<T>(x - aVector.x, y - aVector.y, z - aVector.z);
}

template<class T>
inline SC_TVector3<T> SC_TVector3<T>::operator-(const T& aValue) const
{
	return SC_TVector3<T>(x - aValue, y - aValue, z - aValue);
}

template<class T>
inline SC_TVector3<T> operator-(const T& aValue, const SC_TVector3<T>& aVector)
{
	return SC_TVector3<T>(aValue - aVector.x, aValue - aVector.y, aValue - aVector.z);
}

template<class T>
inline SC_TVector3<T>& SC_TVector3<T>::operator*=(const SC_TVector3& aVector)
{
	x *= aVector.x;
	y *= aVector.y;
	z *= aVector.z;
	return *this;
}

template<class T>
inline SC_TVector3<T>& SC_TVector3<T>::operator*=(const T& aValue)
{
	x *= aValue;
	y *= aValue;
	z *= aValue;
	return *this;
}

template<class T>
inline SC_TVector3<T> SC_TVector3<T>::operator*(const SC_TVector3& aVector) const
{
	return SC_TVector3<T>(x * aVector.x, y * aVector.y, z * aVector.z);
}

template<class T>
inline SC_TVector3<T> SC_TVector3<T>::operator*(const T& aValue) const
{
	return SC_TVector3<T>(x * aValue, y * aValue, z * aValue);
}

template<class T>
inline SC_TVector3<T> operator*(const T& aValue, const SC_TVector3<T>& aVector)
{
	return SC_TVector3<T>(aValue * aVector.x, aValue * aVector.y, aValue * aVector.z);
}

template<class T>
inline SC_TVector3<T>& SC_TVector3<T>::operator+=(const SC_TVector3& aVector)
{
	x += aVector.x;
	y += aVector.y;
	z += aVector.z;
	return *this;
}

template<class T>
inline SC_TVector3<T>& SC_TVector3<T>::operator+=(const T& aValue)
{
	x += aValue;
	y += aValue;
	z += aValue;
	return *this;
}

template<class T>
inline SC_TVector3<T> SC_TVector3<T>::operator+(const SC_TVector3& aVector) const
{
	return SC_TVector3<T>(x + aVector.x, y + aVector.y, z + aVector.z);
}

template<class T>
inline SC_TVector3<T> SC_TVector3<T>::operator+(const T& aValue) const
{
	return SC_TVector3<T>(x + aValue, y + aValue, z + aValue);
}

template<class T>
inline SC_TVector3<T> operator+(const T& aValue, const SC_TVector3<T>& aVector)
{
	return SC_TVector3<T>(aValue + aVector.x, aValue + aVector.y, aValue + aVector.z);
}

template<class T>
inline SC_TVector3<T>& SC_TVector3<T>::operator/=(const SC_TVector3& aVector)
{
	x /= aVector.x;
	y /= aVector.y;
	z /= aVector.z;
	return *this;
}

template<class T>
inline SC_TVector3<T>& SC_TVector3<T>::operator/=(const T& aValue)
{
	x /= aValue;
	y /= aValue;
	z /= aValue;
	return *this;
}

template<class T>
inline SC_TVector3<T> SC_TVector3<T>::operator/(const SC_TVector3& aVector) const
{
	return SC_TVector3<T>(x / aVector.x, y / aVector.y, z / aVector.z);
}

template<class T>
inline SC_TVector3<T> SC_TVector3<T>::operator/(const T& aValue) const
{
	return SC_TVector3<T>(x / aValue, y / aValue, z / aValue);
}

template<class T>
inline SC_TVector3<T> operator/(const T& aValue, const SC_TVector3<T>& aVector)
{
	return SC_TVector3<T>(aValue / aVector.x, aValue / aVector.y, aValue / aVector.z);
}

using SC_Vector = SC_TVector3<float>;
using SC_Vector3d = SC_TVector3<double>;
using SC_Vector3i = SC_TVector3<int32>;
using SC_Vector3ui = SC_TVector3<uint32>;

//ProjectFilter(Math)
#pragma once

#ifndef __SC_VECTOR_HEADER__
#error Please include SC_Vector.h instead.
#endif

template<class T>
class SC_TVector2
{
public:
	union
	{
		struct { T x, y; };
		T mData[2];
	};

	static const SC_TVector2 gZeroVector;
	static const SC_TVector2 gOneVector;

public:
	SC_TVector2();
	SC_TVector2(T aScalar);
	SC_TVector2(T aX, T aY);
	SC_TVector2(const SC_TVector2& aVec);

	void Normalize();
	SC_TVector2 GetNormalized() const;

	T Length() const;
	T Length2() const;

	SC_TVector2 XX() const { return SC_TVector2(x, x); }
	SC_TVector2 YX() const { return SC_TVector2(y, x); }
	SC_TVector2 YY() const { return SC_TVector2(y, y); }

	//Negate operator
	SC_TVector2 operator-() const;

	// Subtraction operators
	SC_TVector2& operator-=(const SC_TVector2& aVector);
	SC_TVector2& operator-=(const T& aValue);
	SC_TVector2 operator-(const SC_TVector2& aVector) const;
	SC_TVector2 operator-(const T& aValue) const;

	//Multiplication operators
	SC_TVector2& operator*=(const SC_TVector2& aVector);
	SC_TVector2& operator*=(const T& aValue);
	SC_TVector2 operator*(const SC_TVector2& aVector) const;
	SC_TVector2 operator*(const T& aValue) const;

	//Addition operators
	SC_TVector2& operator+=(const SC_TVector2& aVector);
	SC_TVector2& operator+=(const T& aValue);
	SC_TVector2 operator+(const SC_TVector2& aVector) const;
	SC_TVector2 operator+(const T& aValue) const;

	//Division operators
	SC_TVector2& operator/=(const SC_TVector2& aVector);
	SC_TVector2& operator/=(const T& aValue);
	SC_TVector2 operator/(const SC_TVector2& aVector) const;
	SC_TVector2 operator/(const T& aValue) const;
};

template<class T>
inline SC_TVector2<T>::SC_TVector2()
	: x(static_cast<T>(0)), y(static_cast<T>(0))
{
}

template<class T>
inline SC_TVector2<T>::SC_TVector2(T aScalar)
	: x(aScalar), y(aScalar)
{
}

template<class T>
inline SC_TVector2<T>::SC_TVector2(T aX, T aY)
	: x(aX), y(aY)
{
}

template<class T>
inline SC_TVector2<T>::SC_TVector2(const SC_TVector2& aVec)
	: x(aVec.x), y(aVec.y)
{
}

template<class T>
inline void SC_TVector2<T>::Normalize()
{
	const float l2 = x*x + y*y;
	if (l2 > 0.f)
	{
		const float scale = SC_InvSqrt(l2);
		x *= scale;
		y *= scale;
	}
}

template<class T>
inline SC_TVector2<T> SC_TVector2<T>::GetNormalized() const
{
	SC_TVector2 v(*this);
	return v.Normalize();
}

template<class T>
inline T SC_TVector2<T>::Length() const
{
	return SC_Sqrt(x*x + y*y);
}

template<class T>
inline T SC_TVector2<T>::Length2() const
{
	return (x*x + y*y);
}

template<class T>
inline SC_TVector2<T> SC_TVector2<T>::operator-() const
{
	return SC_TVector2(-x, -y);
}

template<class T>
inline SC_TVector2<T>& SC_TVector2<T>::operator-=(const SC_TVector2& aVector)
{
	x -= aVector.x;
	y -= aVector.y;
	return *this;
}

template<class T>
inline SC_TVector2<T>& SC_TVector2<T>::operator-=(const T& aValue)
{
	x -= aValue;
	y -= aValue;
	return *this;
}

template<class T>
inline SC_TVector2<T> SC_TVector2<T>::operator-(const SC_TVector2& aVector) const
{
	return SC_TVector2<T>(x - aVector.x, y - aVector.y);
}

template<class T>
inline SC_TVector2<T> SC_TVector2<T>::operator-(const T& aValue) const
{
	return SC_TVector2<T>(x - aValue, y - aValue);
}

template<class T>
inline SC_TVector2<T> operator-(const T& aValue, const SC_TVector2<T>& aVector)
{
	return SC_TVector2<T>(aValue - aVector.x, aValue - aVector.y);
}

template<class T>
inline SC_TVector2<T>& SC_TVector2<T>::operator*=(const SC_TVector2& aVector)
{
	x *= aVector.x;
	y *= aVector.y;
	return *this;
}

template<class T>
inline SC_TVector2<T>& SC_TVector2<T>::operator*=(const T& aValue)
{
	x *= aValue;
	y *= aValue;
	return *this;
}

template<class T>
inline SC_TVector2<T> SC_TVector2<T>::operator*(const SC_TVector2& aVector) const
{
	return SC_TVector2<T>(x * aVector.x, y * aVector.y);
}

template<class T>
inline SC_TVector2<T> SC_TVector2<T>::operator*(const T& aValue) const
{
	return SC_TVector2<T>(x * aValue, y * aValue);
}

template<class T>
inline SC_TVector2<T> operator*(const T& aValue, const SC_TVector2<T>& aVector)
{
	return SC_TVector2<T>(aValue * aVector.x, aValue * aVector.y);
}

template<class T>
inline SC_TVector2<T>& SC_TVector2<T>::operator+=(const SC_TVector2& aVector)
{
	x += aVector.x;
	y += aVector.y;
	return *this;
}

template<class T>
inline SC_TVector2<T>& SC_TVector2<T>::operator+=(const T& aValue)
{
	x += aValue;
	y += aValue;
	return *this;
}

template<class T>
inline SC_TVector2<T> SC_TVector2<T>::operator+(const SC_TVector2& aVector) const
{
	return SC_TVector2<T>(x + aVector.x, y + aVector.y);
}

template<class T>
inline SC_TVector2<T> SC_TVector2<T>::operator+(const T& aValue) const
{
	return SC_TVector2<T>(x + aValue, y + aValue);
}

template<class T>
inline SC_TVector2<T> operator+(const T& aValue, const SC_TVector2<T>& aVector)
{
	return SC_TVector2<T>(aValue + aVector.x, aValue + aVector.y);
}

template<class T>
inline SC_TVector2<T>& SC_TVector2<T>::operator/=(const SC_TVector2& aVector)
{
	x /= aVector.x;
	y /= aVector.y;
	return *this;
}

template<class T>
inline SC_TVector2<T>& SC_TVector2<T>::operator/=(const T& aValue)
{
	x /= aValue;
	y /= aValue;
	return *this;
}

template<class T>
inline SC_TVector2<T> SC_TVector2<T>::operator/(const SC_TVector2& aVector) const
{
	return SC_TVector2<T>(x / aVector.x, y / aVector.y);
}

template<class T>
inline SC_TVector2<T> SC_TVector2<T>::operator/(const T& aValue) const
{
	return SC_TVector2<T>(x / aValue, y / aValue);
}

template<class T>
inline SC_TVector2<T> operator/(const T& aValue, const SC_TVector2<T>& aVector)
{
	return SC_TVector2<T>(aValue / aVector.x, aValue / aVector.y);
}

using SC_Vector2 = SC_TVector2<float>;
using SC_Vector2d = SC_TVector2<double>;
using SC_Vector2i = SC_TVector2<int32>;
using SC_Vector2ui = SC_TVector2<uint32>;
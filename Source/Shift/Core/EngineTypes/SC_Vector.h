//ProjectFilter(Math)
#pragma once
#define __SC_VECTOR_HEADER__

template<class T>
class SC_TVector2;
template<class T>
class SC_TVector3;
template<class T>
class SC_TVector4;

#include "SC_Vector2.h"
#include "SC_Vector3.h"
#include "SC_Vector4.h"

template<typename T> inline SC_TVector2<T> operator+(const float aScalar, const SC_TVector2<T>& aVector) { return SC_TVector2<T>(aScalar + aVector.x, aScalar + aVector.y); }
template<typename T> inline SC_TVector2<T> operator-(const float aScalar, const SC_TVector2<T>& aVector) { return SC_TVector2<T>(aScalar - aVector.x, aScalar - aVector.y); }
template<typename T> inline SC_TVector2<T> operator*(const float aScalar, const SC_TVector2<T>& aVector) { return SC_TVector2<T>(aScalar * aVector.x, aScalar * aVector.y); }
template<typename T> inline SC_TVector2<T> operator/(const float aScalar, const SC_TVector2<T>& aVector) { return SC_TVector2<T>(aScalar / aVector.x, aScalar / aVector.y); }

template<typename T> inline SC_TVector3<T> operator+(const float aScalar, const SC_TVector3<T>& aVector) { return SC_TVector3<T>(aScalar + aVector.x, aScalar + aVector.y, aScalar + aVector.z); }
template<typename T> inline SC_TVector3<T> operator-(const float aScalar, const SC_TVector3<T>& aVector) { return SC_TVector3<T>(aScalar - aVector.x, aScalar - aVector.y, aScalar - aVector.z); }
template<typename T> inline SC_TVector3<T> operator*(const float aScalar, const SC_TVector3<T>& aVector) { return SC_TVector3<T>(aScalar * aVector.x, aScalar * aVector.y, aScalar * aVector.z); }
template<typename T> inline SC_TVector3<T> operator/(const float aScalar, const SC_TVector3<T>& aVector) { return SC_TVector3<T>(aScalar / aVector.x, aScalar / aVector.y, aScalar / aVector.z); }

template<typename T> inline SC_TVector4<T> operator+(const float aScalar, const SC_TVector4<T>& aVector) { return SC_TVector4<T>(aScalar + aVector.x, aScalar + aVector.y, aScalar + aVector.z, aScalar + aVector.w); }
template<typename T> inline SC_TVector4<T> operator-(const float aScalar, const SC_TVector4<T>& aVector) { return SC_TVector4<T>(aScalar - aVector.x, aScalar - aVector.y, aScalar - aVector.z, aScalar - aVector.w); }
template<typename T> inline SC_TVector4<T> operator*(const float aScalar, const SC_TVector4<T>& aVector) { return SC_TVector4<T>(aScalar * aVector.x, aScalar * aVector.y, aScalar * aVector.z, aScalar * aVector.w); }
template<typename T> inline SC_TVector4<T> operator/(const float aScalar, const SC_TVector4<T>& aVector) { return SC_TVector4<T>(aScalar / aVector.x, aScalar / aVector.y, aScalar / aVector.z, aScalar * aVector.w); }
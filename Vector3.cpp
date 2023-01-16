#include "Vector3.h"
#include <cmath>		//sqat

Vector3::Vector3()
{
}

Vector3::Vector3(float x, float y, float z):x(x),y(y),z(z)
{
}
float Vector3::length() const {
	return sqrtf(x * x + y * y + z * z);
}

Vector3& Vector3::normalize() {
	float len = length();
	if (len != 0)
	{
		return *this /= len;
	}
	return *this;
}

float Vector3::dot(const Vector3& v) const
{
	return x * v.x + y * v.y + z * v.z;
}

Vector3 Vector3::cross(const Vector3& v) const
{
	Vector3 vec3;
	vec3.x = y * v.z - z * v.y;
	vec3.y = z * v.x - x * v.z;
	vec3.z = x * v.y - y * v.x;

	return vec3;
}
//補間関数
	//線形補間(1次関数補間)
const Vector3 lerp(const Vector3& start, const Vector3& end, const float t)
{
	//float y=t;
	//return start * (1.0f - y) + end * y;
	return start * (1.0f - t) + end * t;
}
const Vector3 Bezier2(const Vector3& p0, const Vector3& p1, const Vector3& p2, const float t)
{
	return (1.0f - t) * (1.0f - t) * p0 + 2.0f * (1.0f - t) * t * p1 + t * t * p2;
}

const Vector3 Bezier3(const Vector3& p0, const Vector3& p1, const Vector3& p2, const Vector3& p3, const float t)
{
	return (1.0f - t) * (1.0f - t) * (1.0f - t) * p0 + 3.0f * (1.0f - t) * (1.0f - t) * t *
		p1 + 3 * (1.0f - t) * t * t * p2 + t * t * t * p3;
}

Vector3 Vector3::operator+()const
{
	return *this;
}

Vector3 Vector3::operator-()const
{
	return Vector3(-*this);
}

Vector3& Vector3::operator+=(const Vector3& v)
{
	x += v.x;
	y += v.y;
	z += v.z;

	return *this;
}

Vector3& Vector3::operator-=(const Vector3& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;

	return *this;
}

Vector3& Vector3::operator*=(float s)
{
	x *= s;
	y *= s;
	z *= s;
	return *this;
}

Vector3& Vector3::operator/=(float s)
{
	x /= s;
	y /= s;
	z /= s;
	return *this;
}

//Vector2 クラスに属さない関数群
//二項演算子
const Vector3 operator+(const Vector3& v1, const Vector3& v2)
{
	Vector3 temp(v1);
	return temp += v2;
}

const Vector3 operator-(const Vector3& v1, const Vector3& v2)
{
	Vector3 temp(v1);
	return temp -= v2;
}

const Vector3 operator*(const Vector3& v, float s)
{
	Vector3 temp(v);
	return temp *= s;
}

const Vector3 operator*(float s, const Vector3& v)
{
	return v * s;
}

const Vector3 operator/(const Vector3& v, float s)
{
	Vector3 temp(v);
	return temp /= s;
}
#include "Vector2.h"
#include <cmath>		//sqat

Vector2* vec = new Vector2;

Vector2::Vector2()
	:Vector2(0,0)
{
}

Vector2::Vector2(float x, float y)
	:x(x),y(y)
{
}

float Vector2::length() const
{
	return (x*x)+(y*y);
}

Vector2& Vector2::normalize()
{
	float len = length();
	if (len != 0)
	{
		return *this /= len;

	}
	return *this;
}

float Vector2::dot(const Vector2& v) const
{
	return x * v.x + y * v.y;
}

float Vector2::cross(const Vector2& v) const
{
	return x * v.y - y * v.x;
}

Vector2 Vector2::operator+() const
{
	return *this;
}

Vector2 Vector2::operator-() const
{
	return Vector2(-x, -y);
}

Vector2& Vector2::operator+=(const Vector2& v)
{
	x += v.x;
	y += v.y;
	return *this;
}

Vector2& Vector2::operator-=(const Vector2& v)
{
	x -= v.x;
	y -= v.y;
	return *this;
}

Vector2& Vector2::operator*=(float s)
{
	x *= s;
	y *= s;
	return *this;
}

Vector2& Vector2::operator/=(float s)
{
	x /= s;
	y /= s;
	return *this;
}

// Vector2 �N���X���ɑ����Ȃ��֐��Q
//�񍀉��Z�q
const Vector2 operator+(const Vector2& v1, const Vector2& v2)
{
	Vector2 temp(v1);
	return temp += v2;

}

const Vector2 operator-(const Vector2& v1, const Vector2& v2)
{
	Vector2 temp(v1);
	return temp -= v2;
}

const Vector2 operator*(const Vector2& v, float s)
{
	Vector2 temp(v);
	return s * v;
}

const Vector2 operator*(float s,const Vector2& v)
{
	return v * s;
}

const Vector2 operator/(const Vector2& v, float s)
{
	Vector2 temp(v);
	return v / s;
}
#include "Quaternion.h"

Quaternion::Quaternion()
{
}

Quaternion::Quaternion(float x, float y, float z, float w) :x(x), y(y), z(z), w(w)
{
}

float Quaternion::dot(const Quaternion& q1, const Quaternion& q2)
{
	return q1.x * q2.x + q1.y * q2.y + q1.z * q2.z;
}

Vector3 Quaternion::cross(const Vector3& q1, const Vector3& q2)
{
	Vector3 Q;
	Q.x = q1.y * q2.z - q1.z * q2.y;
	Q.y = q1.z * q2.x - q1.x * q2.z;
	Q.z = q1.x * q2.y - q1.y * q2.x;

	return Q;
}

Quaternion Quaternion::Multiply(const Quaternion& lhs, const Quaternion& rhs)
{
	Vector3 lv(lhs.x, lhs.y, lhs.z);
	Vector3 rv(rhs.x, rhs.y, rhs.z);

	Vector3 lrv;
	Quaternion lr;

	lrv = cross(lv, rv) + rhs.w * lv + lhs.w * rv;

	lr.w = lhs.w * rhs.w - dot(lhs, rhs);

	lr = { lrv.x,lrv.y,lrv.z,lr.w };

	return lr;
}

Quaternion Quaternion::Identity()
{
	return Quaternion(0.0f, 0.0f, 0.0f, 1.0f);
}

Quaternion Quaternion::Conjugate(const Quaternion& q)
{
	return Quaternion(-q.x, -q.y, -q.z, q.w);
}

float Quaternion::norm(const Quaternion& q)
{
	return sqrtf(q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w);
}

Quaternion Quaternion::Normalize(const Quaternion& q)
{
	float len = norm(q);
	if (len != 0.0f)
	{
		return q / len;
	}
	return *this;
}

Quaternion Quaternion::Inverse(const Quaternion& q)
{
	float len = norm(q);
	if (len != 0.0f)
	{
		Quaternion in;
		in.x = 1.0f * Conjugate(q).x / (len * len);
		in.y = 1.0f * Conjugate(q).y / (len * len);
		in.z = 1.0f * Conjugate(q).z / (len * len);
		in.w = 1.0f * Conjugate(q).w / (len * len);
		return in;
	}
	return *this;
}

//”CˆÓ²‰ñ“]‚ğ•\‚·Quaternion‚Ì¶¬(angle‚Ì³‹K‰»‚Í•K{)
Quaternion Quaternion::MakeAxisAngle(const Vector3& axis, float angle)
{
	Quaternion result;
	result.x = axis.x * sinf(angle / 2.0f);
	result.y = axis.y * sinf(angle / 2.0f);
	result.z = axis.z * sinf(angle / 2.0f);
	result.w = cosf(angle / 2.0f);

	return result;
}

//ƒxƒNƒgƒ‹‚ğQuaternion‚Å‰ñ“]‚³‚¹‚½Œ‹‰Ê‚ÌƒxƒNƒgƒ‹‚ğ‹‚ß‚é
Vector3 Quaternion::RotateVector(const Vector3& v, const Quaternion& q)
{
	Vector3 result;
	Quaternion Q = q * v * Identity();

	result.x = Q.x;
	result.y = Q.y;
	result.z = Q.z;

	return result;
}

//Quaternion‚©‚ç‰ñ“]s—ñ‚ğ‹‚ß‚é
Matrix4 Quaternion::MakeRotateMatrix(const Quaternion& q)
{
	Matrix4 result
	{
		q.w * q.w + q.x * q.x - q.y * q.y - q.z * q.z,2.0f * (q.x * q.y + q.w * q.z),2.0f * (q.x * q.z - q.w * q.y),0.0f,
		2.0f * (q.x * q.y - q.w * q.z),q.w * q.w - q.x * q.x + q.y * q.y - q.z * q.z,2.0f * (q.y * q.z + q.w * q.x),0.0f,
		2.0f * (q.x * q.z + q.w * q.y),2.0f * (q.y * q.z - q.w * q.x),q.w * q.w - q.x * q.x - q.y * q.y + q.z * q.z,0.0f,
		0.0f,0.0f,0.0f,1.0f
	};
	return result;
}


Quaternion Quaternion::operator+()const
{
	return *this;
}

Quaternion Quaternion::operator-()const
{

	return Quaternion(-x, -y, -z, -w);
}

Quaternion& Quaternion::operator+=(const Quaternion& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	w += v.w;

	return *this;
}

Quaternion& Quaternion::operator-=(const Quaternion& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	w -= v.w;

	return *this;
}

Quaternion& Quaternion::operator*=(float s)
{
	x *= s;
	y *= s;
	z *= s;
	w *= s;
	return *this;
}

Quaternion& Quaternion::operator/=(float s)
{
	x /= s;
	y /= s;
	z /= s;
	w /= s;

	return *this;
}

//QuaternionƒNƒ‰ƒX‚É‘®‚³‚È‚¢ŠÖ”ŒQ
//“ñ€‰‰Zq
const Quaternion operator+(const Quaternion& v1, const Quaternion& v2)
{
	Quaternion temp(v1);
	return temp += v2;
}

const Quaternion operator-(const Quaternion& v1, const Quaternion& v2)
{
	Quaternion temp(v1);
	return temp -= v2;
}

const Quaternion operator*(const Quaternion& v, float s)
{
	Quaternion temp(v);
	return temp *= s;
}

const Quaternion operator*(const Quaternion& q, const Vector3& v)
{
	Quaternion temp(q);
	temp.x *= v.x;
	temp.y *= v.y;
	temp.z *= v.z;

	return temp;
}

const Quaternion operator*(const Quaternion & q1, const Quaternion& q2)
{
	return q1 * q2;
}

const Quaternion operator*(const Vector3& v, const Quaternion& q)
{
	return v * q;
}

const Quaternion operator*(float s, const Quaternion& v)
{
	return v * s;
}

const Quaternion operator/(const Quaternion& v, float s)
{
	Quaternion temp(v);
	return temp /= s;
}
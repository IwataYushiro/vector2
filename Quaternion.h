#pragma once
#include "Vector3.h"

class Quaternion
{
public:
	float x;//x成分
	float y;//y成分
	float z;//z成分
	float w;//w成分

public:
	//コンストラクタ
	Quaternion();								//零ベクトルとして生成
	Quaternion(float x, float y, float z, float w);		//x成分、y成分、z成分を指定して生成

	//内積
	float dot(const Quaternion& q1, const Quaternion& q2);
	//外積 
	Vector3 cross(const Vector3& q1, const Vector3& q2);
	//Quaternionの積
	Quaternion Multiply(const Quaternion& lhs, const Quaternion& rhs);
	//単位Quaternionを返す
	Quaternion Identity();
	//共役Quaternionを返す
	Quaternion Conjugate(const Quaternion& quaternion);
	//Quaternionのnormを返す
	float norm(const Quaternion& quaternion);
	//正規化したQuaternionを返す
	Quaternion Normalize(const Quaternion& quaternion);
	//逆Quaternionを返す
	Quaternion Inverse(const Quaternion& quaternion);

	//単項演算子オーバーロード
	Quaternion operator+() const;
	Quaternion operator-() const;

	//代入演算子オーバーロード
	Quaternion& operator+=(const Quaternion& v);
	Quaternion& operator-=(const Quaternion& v);
	Quaternion& operator*=(float s);
	Quaternion& operator/=(float s);
};

//2項演算子オーバーロード
//パターンの準備
const Quaternion operator+(const Quaternion& v1, const Quaternion& v2);
const Quaternion operator-(const Quaternion& v1, const Quaternion& v2);
const Quaternion operator*(const Quaternion& v, float s);
const Quaternion operator*(float s, const Quaternion& v);
const Quaternion operator/(const Quaternion& v, float s);
#pragma once
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
};


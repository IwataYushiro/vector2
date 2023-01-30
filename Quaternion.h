#pragma once
#include "Vector3.h"

class Quaternion
{
public:
	float x;//x����
	float y;//y����
	float z;//z����
	float w;//w����

public:
	//�R���X�g���N�^
	Quaternion();								//��x�N�g���Ƃ��Đ���
	Quaternion(float x, float y, float z, float w);		//x�����Ay�����Az�������w�肵�Đ���

	//����
	float dot(const Quaternion& q1, const Quaternion& q2);
	//�O�� 
	Vector3 cross(const Vector3& q1, const Vector3& q2);
	//Quaternion�̐�
	Quaternion Multiply(const Quaternion& lhs, const Quaternion& rhs);
	//�P��Quaternion��Ԃ�
	Quaternion Identity();
	//����Quaternion��Ԃ�
	Quaternion Conjugate(const Quaternion& quaternion);
	//Quaternion��norm��Ԃ�
	float norm(const Quaternion& quaternion);
	//���K������Quaternion��Ԃ�
	Quaternion Normalize(const Quaternion& quaternion);
	//�tQuaternion��Ԃ�
	Quaternion Inverse(const Quaternion& quaternion);

	//�P�����Z�q�I�[�o�[���[�h
	Quaternion operator+() const;
	Quaternion operator-() const;

	//������Z�q�I�[�o�[���[�h
	Quaternion& operator+=(const Quaternion& v);
	Quaternion& operator-=(const Quaternion& v);
	Quaternion& operator*=(float s);
	Quaternion& operator/=(float s);
};

//2�����Z�q�I�[�o�[���[�h
//�p�^�[���̏���
const Quaternion operator+(const Quaternion& v1, const Quaternion& v2);
const Quaternion operator-(const Quaternion& v1, const Quaternion& v2);
const Quaternion operator*(const Quaternion& v, float s);
const Quaternion operator*(float s, const Quaternion& v);
const Quaternion operator/(const Quaternion& v, float s);
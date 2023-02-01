#pragma once
#include "Vector3.h"
#include "Matrix4.h"

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
	Quaternion Conjugate(const Quaternion& q);
	//Quaternion��norm��Ԃ�
	float norm(const Quaternion& q);
	//���K������Quaternion��Ԃ�
	Quaternion Normalize(const Quaternion& q);
	//�tQuaternion��Ԃ�
	Quaternion Inverse(const Quaternion& q);
	//�C�ӎ���]��\��Quaternion�̐���(angle�̐��K���͕K�{)
	Quaternion MakeAxisAngle(const Vector3& axis, float angle);
	//�x�N�g����Quaternion�ŉ�]���������ʂ̃x�N�g�������߂�
	Vector3 RotateVector(const Vector3& v, const Quaternion& q);
	//Quaternion�����]�s������߂�
	Matrix4 MakeRotateMatrix(const Quaternion& q);
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
const Quaternion operator*(const Quaternion& q, const Vector3& v);
const Quaternion operator*(const Quaternion& q1, const Quaternion& q2);
const Quaternion operator*(const Vector3& v, const Quaternion& q);
const Quaternion operator*(float s, const Quaternion& v);
const Quaternion operator/(const Quaternion& v, float s);
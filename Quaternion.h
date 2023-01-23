#pragma once
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
};


/*

//�֐��v���g�^�C�v�錾
//���̍쐬
int DrawSphere3D(const Vector3& CenterPos, const float r, const int DivNum,
	const unsigned int DifColor, const unsigned int SpcColor, const int FillFlag);

//3D�̐�
int DrawLine3D(const Vector3& Pos1, const Vector3& Pos2, const unsigned int Color);

//�~���쐬
int DrawCone3D(const Vector3& TopPos, const Vector3& BottomPos, const float r,
	const int DivNum, const unsigned int DifColor, const unsigned int SpcColor, const int FillFlag);

//�J�����̈ʒu�Ǝp���̐ݒ�
int SetCameraPositionAndTargetAndUpVec(
	const Vector3& cameraPosition,		//�J�����̈ʒu
	const Vector3& cameraTarget,		//�J�����̒����_
	const Vector3& cameraUp				//�J�����̏�̌���
);

//���f���̍��W�ϊ��p�s����Z�b�g
//int MV1SetMatrix(const int MHandle, const Matrix4 Matrix);
//x,y,z���`��
void DrawAxis3D(const float length);	//x,y,z���̕`��
//�L�[����̕`��
void DrawKeyOperation();

//���`�� DifColor=���̐F,SpcColor=���̐F,FillFlag=0=���C���[�t���[��,1=�h��Ԃ�
int DrawSphere3D(const Vector3& CenterPos, const float r, const int DivNum,
	const unsigned int DifColor, const unsigned int SpcColor, const int FillFlag)
{
	VECTOR centerPos = { CenterPos.x,CenterPos.y,CenterPos.z };

	return DrawSphere3D(centerPos, r, DivNum, DifColor, SpcColor, FillFlag);
}
//�����`��
int DrawLine3D(const Vector3& Pos1, const Vector3& Pos2, const unsigned int Color)
{
	VECTOR p1 = { Pos1.x,Pos1.y,Pos1.z };
	VECTOR p2 = { Pos2.x,Pos2.y,Pos2.z };

	return DrawLine3D(p1, p2, Color);
}
//�~���쐬
int DrawCone3D(const Vector3& TopPos, const Vector3& BottomPos, const float r,
	const int DivNum, const unsigned int DifColor, const unsigned int SpcColor, const int FillFlag)
{
	VECTOR topPos = { TopPos.x,TopPos.y,TopPos.z };
	VECTOR bottomPos = { BottomPos.x,BottomPos.y,BottomPos.z };

	return DrawCone3D(topPos, bottomPos, r, DivNum, DifColor, SpcColor, FillFlag);
}

//�J�������W
int SetCameraPositionAndTargetAndUpVec(
	const Vector3& cameraPosition,		//�J�����̈ʒu
	const Vector3& cameraTarget,		//�J�����̒����_
	const Vector3& cameraUp				//�J�����̏�̌���
)
{
	VECTOR position = { cameraPosition.x,cameraPosition.y,cameraPosition.z };
	VECTOR target = { cameraTarget.x, cameraTarget.y, cameraTarget.z };
	VECTOR up = { cameraUp.x,cameraUp.y,cameraUp.z };

	return SetCameraPositionAndTargetAndUpVec(position, target, up);
}

////���f���̍��W�ϊ��p�s����Z�b�g
//int MV1SetMatrix(const int MHandle, const Matrix4 Matrix)
//{
//	MATRIX matrix;
//	std::memcpy(&matrix, &Matrix, sizeof MATRIX);	//�������ԃR�s�[
//
//	return MV1SetMatrix(MHandle, matrix);
//}

//x,y,z���`��
void DrawAxis3D(const float length)
{
	//���̐�
	DrawLine3D(Vector3(-length, 0.0f, 0.0f), Vector3(+length, 0.0f, 0.0f), GetColor(255, 0, 0));//X��
	DrawLine3D(Vector3(0.0f, -length, 0.0f), Vector3(0.0f, +length, 0.0f), GetColor(0, 255, 0));//Y��
	DrawLine3D(Vector3(0.0f, 0.0f, -length), Vector3(0.0f, 0.0f, +length), GetColor(0, 0, 255));//Z��

	//���̐�̕`��
	const float ConeSize = 10.0f;

	DrawCone3D(Vector3(length, 0.0f, 0.0f), Vector3(length - ConeSize, 0.0f, 0.0f), ConeSize / 2, 16,
		GetColor(255, 0, 0), GetColor(255, 255, 255), TRUE);

	DrawCone3D(Vector3(0.0f, length, 0.0f), Vector3(0.0f, length - ConeSize, 0.0f), ConeSize / 2, 16,
		GetColor(0, 255, 0), GetColor(255, 255, 255), TRUE);

	DrawCone3D(Vector3(0.0f, 0.0f, length), Vector3(0.0f, 0.0f, length - ConeSize), ConeSize / 2, 16,
		GetColor(0, 0, 255), GetColor(255, 255, 255), TRUE);
}

//�L�[����`��
void DrawKeyOperation()
{
	DrawFormatString(10, 20 * 1, GetColor(255, 255, 255), "�@[W][E][R]�@R : ���Z�b�g");
	DrawFormatString(10, 20 * 2, GetColor(255, 255, 255), "[A][S][D]�@�@AD: Y������̉�]");
	DrawFormatString(10, 20 * 3, GetColor(255, 255, 255), " [Z]		�@�@WS: X������̉�]");
	DrawFormatString(10, 20 * 4, GetColor(255, 255, 255), "�@			EZ: Z������̉�]");
}

*/
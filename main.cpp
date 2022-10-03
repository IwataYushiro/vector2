#include "DxLib.h"
#include "Vector3.h"
#include "Matrix4.h"
#include <cstring>

// �E�B���h�E�̃^�C�g���ɕ\�����镶����
const char TITLE[] = "LE2B_07_�C���^_���E�V���E";

// �E�B���h�E����
const int WIN_WIDTH = 1024;

// �E�B���h�E�c��
const int WIN_HEIGHT = 576;

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
int MV1SetMatrix(const int MHandle, const Matrix4 Matrix);
//x,y,z���`��
void DrawAxis3D(const float length);	//x,y,z���̕`��
//�L�[����̕`��
void DrawKeyOperation();

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine,
	_In_ int nCmdShow) {
	// �E�B���h�E���[�h�ɐݒ�
	ChangeWindowMode(TRUE);

	// �E�B���h�E�T�C�Y���蓮�ł͕ύX�������A
	// ���E�B���h�E�T�C�Y�ɍ��킹�Ċg��ł��Ȃ��悤�ɂ���
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);

	// �^�C�g����ύX
	SetMainWindowText(TITLE);

	// ��ʃT�C�Y�̍ő�T�C�Y�A�J���[�r�b�g����ݒ�(���j�^�[�̉𑜓x�ɍ��킹��)
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);

	// ��ʃT�C�Y��ݒ�(�𑜓x�Ƃ̔䗦�Őݒ�)
	SetWindowSizeExtendRate(1.0);

	// ��ʂ̔w�i�F��ݒ肷��
	SetBackgroundColor(0x1f, 0x1e, 0x33);

	// DXlib�̏�����
	if (DxLib_Init() == -1) { return -1; }

	// (�_�u���o�b�t�@)�`���O���t�B�b�N�̈�͗��ʂ��w��
	SetDrawScreen(DX_SCREEN_BACK);

	//Z�o�b�t�@��L���ɂ���
	SetUseZBuffer3D(TRUE);
	//Z�o�b�t�@�ւ̏������݂�L���ɂ���
	SetWriteZBuffer3D(TRUE);

	Vector3 cameraPosition(50.0f, 50.0f, -400.0f);
	Vector3 cameraTarget(0.0f, 0.0f, 0.0f);
	Vector3 cameraUp(0.0f, 1.0f, 0.0f);

	SetCameraNearFar(1.0f, 1000.0f);
	SetCameraScreenCenter(WIN_WIDTH / 2.0f, WIN_HEIGHT / 2.0f);
	SetCameraPositionAndTargetAndUpVec(
		cameraPosition,//�J�����̈ʒu
		cameraTarget,  //�J�����̒����_
		cameraUp	   //�J�����̏�̌���
	);

	// �摜�Ȃǂ̃��\�[�X�f�[�^�̕ϐ��錾�Ɠǂݍ���
	int model = MV1LoadModel("fighter/fighter.mqo");

	// �Q�[�����[�v�Ŏg���ϐ��̐錾
	//x,y,z���̉�]�p�x
	const float ROT_UNIT = 0.05f;
	float rotX = 0.0f;
	float rotY = 0.0f;
	float rotZ = 0.0f;

	// �ŐV�̃L�[�{�[�h���p
	char keys[256] = { 0 };

	// 1���[�v(�t���[��)�O�̃L�[�{�[�h���
	char oldkeys[256] = { 0 };

	// �Q�[�����[�v
	while (true) {
		// �ŐV�̃L�[�{�[�h��񂾂������̂�1�t���[���O�̃L�[�{�[�h���Ƃ��ĕۑ�
		// �ŐV�̃L�[�{�[�h�����擾
		GetHitKeyStateAll(keys);

		// ��ʃN���A
		ClearDrawScreen();
		//---------  ��������v���O�������L�q  ----------//

		// �X�V����
		if (CheckHitKey(KEY_INPUT_A)) rotY += ROT_UNIT;
		if (CheckHitKey(KEY_INPUT_D)) rotY -= ROT_UNIT;

		if (CheckHitKey(KEY_INPUT_W)) rotX += ROT_UNIT;
		if (CheckHitKey(KEY_INPUT_S)) rotX -= ROT_UNIT;

		if (CheckHitKey(KEY_INPUT_E)) rotZ += ROT_UNIT;
		if (CheckHitKey(KEY_INPUT_Z)) rotZ -= ROT_UNIT;
		
		//R�Ń��Z�b�g
		if (CheckHitKey(KEY_INPUT_R))
		{
			rotX = rotY = rotZ = 0.0f;
		}

		//�e��ϊ��s��̌v�Z
		Matrix4 matScale = scale(Vector3(25.0f, 25.0f,25.0f));

		Matrix4 matRotX = rotateX(rotX);
		Matrix4 matRotY = rotateY(rotY);
		Matrix4 matRotZ = rotateZ(rotZ);
		Matrix4 matRot = matRotZ * matRotX * matRotY;

		Matrix4 matWorld = matScale * matRot;

		MV1SetMatrix(model, matWorld);

		// �`�揈��
		ClearDrawScreen();

		DrawAxis3D(200.0f);
		
		MV1DrawModel(model);

		DrawKeyOperation();
		//---------  �����܂łɃv���O�������L�q  ---------//
		// (�_�u���o�b�t�@)����
		ScreenFlip();

		// 20�~���b�ҋ@(�^��60FPS)
		WaitTimer(20);

		// Windows�V�X�e�����炭�������������
		if (ProcessMessage() == -1) {
			break;
		}

		// ESC�L�[�������ꂽ�烋�[�v���甲����
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
			break;
		}
	}
	// Dx���C�u�����I������
	DxLib_End();

	// ����I��
	return 0;
}

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

//���f���̍��W�ϊ��p�s����Z�b�g
int MV1SetMatrix(const int MHandle, const Matrix4 Matrix)
{
	MATRIX matrix;
	std::memcpy(&matrix, &Matrix, sizeof MATRIX);	//�������ԃR�s�[

	return MV1SetMatrix(MHandle, matrix);
}

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
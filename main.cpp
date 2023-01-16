#include "DxLib.h"
#include "Vector3.h"
#include "Matrix4.h"
#include <cstring>

// �E�B���h�E�̃^�C�g���ɕ\�����镶����
const char TITLE[] = "LE2C_03_�C���^_���E�V���E";

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
		Vector3(0.0f, 200.0f, -120.0f),//�J�����̈ʒu
		Vector3(0.0f, 0.0f, 0.0f),  //�J�����̒����_
		Vector3(0.0f, 1.0f, 0.0f)	   //�J�����̏�̌���
	);

	//���Ԍv���ɕK�v�ȃf�[�^
	long long startCount = 0;	//�J�n����
	long long nowCount = 0;		//���ݎ���
	long long elapsedCount = 0;	//�o�ߎ���

	//��ԂŎg���f�[�^(start��end��5�b�Ŋ���������)
	Vector3 start(-100.0f, 0.0f, 0.0f);		//�X�^�[�g�n�_
	Vector3 point1(-50.0f, 0.0f, 100.0f);		//����_
	Vector3 point2(50.0f, 0.0f, -100.0f);		//����_
	Vector3 end(+100.0f, 0.0f, 0.0f);		//�S�[���n�_
	float	maxTime = 5.0f;					//�S�̎���
	float	timeRate;						//���p�[�Z���g���Ԃ��i�񂾂�(��)

	//���̈ʒu
	Vector3 position;

	//���s�O�ɃJ�E���^�l���擾
	startCount = GetNowHiPerformanceCount();

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

		if (CheckHitKey(KEY_INPUT_R))
		{
			startCount = GetNowHiPerformanceCount();
		}
		// �X�V����
		nowCount = GetNowHiPerformanceCount();
		elapsedCount = nowCount - startCount;	//�o�ߎ���=���ݎ���-�J�n����
		float elapsedTime = static_cast<float> (elapsedCount) / 1'000'000.0f;//�}�C�N���b��b�ɒP�ʕϊ�

		//�X�^�[�g�n�_		::	start
		//�S�[���n�_		::	end
		//�o�ߎ���			::	elapsedTime[s]
		//�ړ�������		::	timeRate(%)

		timeRate = min(elapsedTime / maxTime, 1.0f);

		position = Bezier3(start, point1, point2, end, timeRate);
		// �`�揈��
		ClearDrawScreen();
		DrawAxis3D(500.0f);

		//���̕`��
		DrawSphere3D(position, 5.0f, 32, GetColor(255, 0, 0), GetColor(255, 255, 255), TRUE);

		//�ϐ��̒l��\��
		DrawFormatString(0, 0, GetColor(255, 255, 255), "position (%6.1f,%6.1f,%6.1f)",
			position.x, position.y, position.z);

		DrawFormatString(0, 20, GetColor(255, 255, 255), "%7.3f [s]", elapsedTime);
		DrawFormatString(0, 40, GetColor(255, 255, 255), "[R] : Restart");

		DrawFormatString(0, 60, GetColor(255, 255, 255), "p0 (%6.1f,%6.1f,%6.1f)",
			start.x, start.y, start.z);
		DrawFormatString(0, 80, GetColor(255, 255, 255), "p1 (%6.1f,%6.1f,%6.1f)",
			point1.x, point1.y, point1.z);
		DrawFormatString(0, 100, GetColor(255, 255, 255), "p2 (%6.1f,%6.1f,%6.1f)",
			point2.x, point2.y, point2.z);
		DrawFormatString(0, 120, GetColor(255, 255, 255), "p3 (%6.1f,%6.1f,%6.1f)",
			end.x, end.y, end.z);

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
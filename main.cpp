#include "DxLib.h"
#include "Quaternion.h"

// �E�B���h�E�̃^�C�g���ɕ\�����镶����
const char TITLE[] = "LE2C_03_�C���^_���E�V���E";

// �E�B���h�E����
const int WIN_WIDTH = 1024;

// �E�B���h�E�c��
const int WIN_HEIGHT = 576;

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
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

	// �摜�Ȃǂ̃��\�[�X�f�[�^�̕ϐ��錾�Ɠǂݍ���
	Quaternion* q = new Quaternion();
	
	// �Q�[�����[�v�Ŏg���ϐ��̐錾
	const float pi = 3.141592f;

	Quaternion q1 = { 2.0f,3.0f,4.0f,1.0f };
	Quaternion q2 = { 1.0f,3.0f,5.0f,2.0f };
	Quaternion identity = q->Identity();
	Quaternion conj = q->Conjugate(q1);
	Quaternion inv = q->Inverse(q1);
	Quaternion normal = q->Normalize(q1);
	Quaternion mul1 = q->Multiply(q1, q2);
	Quaternion mul2 = q->Multiply(q2, q1);
	float norm = q->norm(q1);

	Quaternion rotation = q->MakeAxisAngle({ 0.0f,0.0f,1.0f }, pi / 2.0f);
	Vector3 pointY = { 0.0f,1.0f,0.0f };
	Matrix4 rotateMatrix = q->MakeRotateMatrix(rotation);
	Vector3 rotateByQuaternion = q->RotateVector(pointY, rotation);
	Vector3 rotateByMatrix = transform(pointY, rotateMatrix);

	Quaternion rot0 = q->MakeAxisAngle({ 0.71f,0.71f,0.0f }, 0.3f);
	Quaternion rot1 = { -rot0.x, -rot0.y, -rot0.z, -rot0.w };

	Quaternion interpolate0 = q->Slerp(rot0, rot1, 0.0f);
	Quaternion interpolate1 = q->Slerp(rot0, rot1, 0.3f);
	Quaternion interpolate2 = q->Slerp(rot0, rot1, 0.5f);
	Quaternion interpolate3 = q->Slerp(rot0, rot1, 0.7f);
	Quaternion interpolate4 = q->Slerp(rot0, rot1, 1.0f);
	
	// �ŐV�̃L�[�{�[�h���p
	char keys[256] = { 0 };

	// 1���[�v(�t���[��)�O�̃L�[�{�[�h���
	char oldkeys[256] = { 0 };

	// �Q�[�����[�v
	while (1)
	{
		// �ŐV�̃L�[�{�[�h��񂾂������̂�1�t���[���O�̃L�[�{�[�h���Ƃ��ĕۑ�
		for (int i = 0; i < 256; ++i)
		{
			oldkeys[i] = keys[i];
		}
		// �ŐV�̃L�[�{�[�h�����擾
		GetHitKeyStateAll(keys);

		// ��ʃN���A
		ClearDrawScreen();
		//---------  ��������v���O�������L�q  ----------//

		// �X�V����
		DrawFormatString(0, 0, GetColor(255, 255, 255), "%f, %f, %f, %f    ::interpolate0,slerp(q0,q1,0.0f)",
			interpolate0.x, interpolate0.y, interpolate0.z, interpolate0.w);
		DrawFormatString(0, 20, GetColor(255, 255, 255), "%f, %f, %f, %f    ::interpolate1,slerp(q0,q1,0.3f)",
			interpolate1.x, interpolate1.y, interpolate1.z, interpolate1.w);
		DrawFormatString(0, 40, GetColor(255, 255, 255), "%f, %f, %f, %f    ::interpolate2,slerp(q0,q1,0.5f)",
			interpolate2.x, interpolate2.y, interpolate2.z, interpolate2.w);
		DrawFormatString(0, 60, GetColor(255, 255, 255), "%f, %f, %f, %f    ::interpolate3,slerp(q0,q1,0.7f)",
			interpolate3.x, interpolate3.y, interpolate3.z, interpolate3.w);
		DrawFormatString(0, 80, GetColor(255, 255, 255), "%f, %f, %f, %f    ::interpolate4,slerp(q0,q1,1.0f)",
			interpolate4.x, interpolate4.y, interpolate4.z, interpolate4.w);
		

		// �`�揈��

		//---------  �����܂łɃv���O�������L�q  ---------//
		// (�_�u���o�b�t�@)����
		ScreenFlip();

		// 20�~���b�ҋ@(�^��60FPS)
		WaitTimer(20);

		// Windows�V�X�e�����炭�������������
		if (ProcessMessage() == -1)
		{
			break;
		}

		// ESC�L�[�������ꂽ�烋�[�v���甲����
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)
		{
			break;
		}
	}
	// Dx���C�u�����I������
	DxLib_End();

	delete q;
	// ����I��
	return 0;
}




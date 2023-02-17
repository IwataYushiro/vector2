#include "DxLib.h"
#include "Quaternion.h"

// ウィンドウのタイトルに表示する文字列
const char TITLE[] = "LE2C_03_イワタ_ユウシロウ";

// ウィンドウ横幅
const int WIN_WIDTH = 1024;

// ウィンドウ縦幅
const int WIN_HEIGHT = 576;

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	// ウィンドウモードに設定
	ChangeWindowMode(TRUE);

	// ウィンドウサイズを手動では変更させず、
	// かつウィンドウサイズに合わせて拡大できないようにする
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);

	// タイトルを変更
	SetMainWindowText(TITLE);

	// 画面サイズの最大サイズ、カラービット数を設定(モニターの解像度に合わせる)
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);

	// 画面サイズを設定(解像度との比率で設定)
	SetWindowSizeExtendRate(1.0);

	// 画面の背景色を設定する
	SetBackgroundColor(0x1f, 0x1e, 0x33);

	// DXlibの初期化
	if (DxLib_Init() == -1) { return -1; }

	// (ダブルバッファ)描画先グラフィック領域は裏面を指定
	SetDrawScreen(DX_SCREEN_BACK);

	// 画像などのリソースデータの変数宣言と読み込み
	Quaternion* q = new Quaternion();
	
	// ゲームループで使う変数の宣言
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
	
	// 最新のキーボード情報用
	char keys[256] = { 0 };

	// 1ループ(フレーム)前のキーボード情報
	char oldkeys[256] = { 0 };

	// ゲームループ
	while (1)
	{
		// 最新のキーボード情報だったものは1フレーム前のキーボード情報として保存
		for (int i = 0; i < 256; ++i)
		{
			oldkeys[i] = keys[i];
		}
		// 最新のキーボード情報を取得
		GetHitKeyStateAll(keys);

		// 画面クリア
		ClearDrawScreen();
		//---------  ここからプログラムを記述  ----------//

		// 更新処理
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
		

		// 描画処理

		//---------  ここまでにプログラムを記述  ---------//
		// (ダブルバッファ)裏面
		ScreenFlip();

		// 20ミリ秒待機(疑似60FPS)
		WaitTimer(20);

		// Windowsシステムからくる情報を処理する
		if (ProcessMessage() == -1)
		{
			break;
		}

		// ESCキーが押されたらループから抜ける
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)
		{
			break;
		}
	}
	// Dxライブラリ終了処理
	DxLib_End();

	delete q;
	// 正常終了
	return 0;
}




#include "DxLib.h"
#include "Vector3.h"
#include "Matrix4.h"
#include <cstring>

// ウィンドウのタイトルに表示する文字列
const char TITLE[] = "LE2B_07_イワタ_ユウシロウ";

// ウィンドウ横幅
const int WIN_WIDTH = 1024;

// ウィンドウ縦幅
const int WIN_HEIGHT = 576;

//関数プロトタイプ宣言
//球体作成
int DrawSphere3D(const Vector3& CenterPos, const float r, const int DivNum,
	const unsigned int DifColor, const unsigned int SpcColor, const int FillFlag);

//3Dの線
int DrawLine3D(const Vector3& Pos1, const Vector3& Pos2, const unsigned int Color);

//円錐作成
int DrawCone3D(const Vector3& TopPos, const Vector3& BottomPos, const float r,
	const int DivNum, const unsigned int DifColor, const unsigned int SpcColor, const int FillFlag);

//カメラの位置と姿勢の設定
int SetCameraPositionAndTargetAndUpVec(
	const Vector3& cameraPosition,		//カメラの位置
	const Vector3& cameraTarget,		//カメラの注視点
	const Vector3& cameraUp				//カメラの上の向き
);

//モデルの座標変換用行列をセット
int MV1SetMatrix(const int MHandle, const Matrix4 Matrix);
//x,y,z軸描画
void DrawAxis3D(const float length);	//x,y,z軸の描画
//キー操作の描画
void DrawKeyOperation();

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine,
	_In_ int nCmdShow) {
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

	//Zバッファを有効にする
	SetUseZBuffer3D(TRUE);
	//Zバッファへの書き込みを有効にする
	SetWriteZBuffer3D(TRUE);

	Vector3 cameraPosition(50.0f, 50.0f, -400.0f);
	Vector3 cameraTarget(0.0f, 0.0f, 0.0f);
	Vector3 cameraUp(0.0f, 1.0f, 0.0f);

	SetCameraNearFar(1.0f, 1000.0f);
	SetCameraScreenCenter(WIN_WIDTH / 2.0f, WIN_HEIGHT / 2.0f);
	SetCameraPositionAndTargetAndUpVec(
		cameraPosition,//カメラの位置
		cameraTarget,  //カメラの注視点
		cameraUp	   //カメラの上の向き
	);

	// 画像などのリソースデータの変数宣言と読み込み
	int model = MV1LoadModel("fighter/fighter.mqo");

	// ゲームループで使う変数の宣言
	//x,y,z軸の回転角度
	const float ROT_UNIT = 0.05f;
	float rotX = 0.0f;
	float rotY = 0.0f;
	float rotZ = 0.0f;

	// 最新のキーボード情報用
	char keys[256] = { 0 };

	// 1ループ(フレーム)前のキーボード情報
	char oldkeys[256] = { 0 };

	// ゲームループ
	while (true) {
		// 最新のキーボード情報だったものは1フレーム前のキーボード情報として保存
		// 最新のキーボード情報を取得
		GetHitKeyStateAll(keys);

		// 画面クリア
		ClearDrawScreen();
		//---------  ここからプログラムを記述  ----------//

		// 更新処理
		if (CheckHitKey(KEY_INPUT_A)) rotY += ROT_UNIT;
		if (CheckHitKey(KEY_INPUT_D)) rotY -= ROT_UNIT;

		if (CheckHitKey(KEY_INPUT_W)) rotX += ROT_UNIT;
		if (CheckHitKey(KEY_INPUT_S)) rotX -= ROT_UNIT;

		if (CheckHitKey(KEY_INPUT_E)) rotZ += ROT_UNIT;
		if (CheckHitKey(KEY_INPUT_Z)) rotZ -= ROT_UNIT;
		
		//Rでリセット
		if (CheckHitKey(KEY_INPUT_R))
		{
			rotX = rotY = rotZ = 0.0f;
		}

		//各種変換行列の計算
		Matrix4 matScale = scale(Vector3(25.0f, 25.0f,25.0f));

		Matrix4 matRotX = rotateX(rotX);
		Matrix4 matRotY = rotateY(rotY);
		Matrix4 matRotZ = rotateZ(rotZ);
		Matrix4 matRot = matRotZ * matRotX * matRotY;

		Matrix4 matWorld = matScale * matRot;

		MV1SetMatrix(model, matWorld);

		// 描画処理
		ClearDrawScreen();

		DrawAxis3D(200.0f);
		
		MV1DrawModel(model);

		DrawKeyOperation();
		//---------  ここまでにプログラムを記述  ---------//
		// (ダブルバッファ)裏面
		ScreenFlip();

		// 20ミリ秒待機(疑似60FPS)
		WaitTimer(20);

		// Windowsシステムからくる情報を処理する
		if (ProcessMessage() == -1) {
			break;
		}

		// ESCキーが押されたらループから抜ける
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
			break;
		}
	}
	// Dxライブラリ終了処理
	DxLib_End();

	// 正常終了
	return 0;
}

//球描画 DifColor=球の色,SpcColor=光の色,FillFlag=0=ワイヤーフレーム,1=塗りつぶし
int DrawSphere3D(const Vector3& CenterPos, const float r, const int DivNum,
	const unsigned int DifColor, const unsigned int SpcColor, const int FillFlag)
{
	VECTOR centerPos = { CenterPos.x,CenterPos.y,CenterPos.z };

	return DrawSphere3D(centerPos, r, DivNum, DifColor, SpcColor, FillFlag);
}
//線分描画
int DrawLine3D(const Vector3& Pos1, const Vector3& Pos2, const unsigned int Color)
{
	VECTOR p1 = { Pos1.x,Pos1.y,Pos1.z };
	VECTOR p2 = { Pos2.x,Pos2.y,Pos2.z };

	return DrawLine3D(p1, p2, Color);
}
//円錐作成
int DrawCone3D(const Vector3& TopPos, const Vector3& BottomPos, const float r,
	const int DivNum, const unsigned int DifColor, const unsigned int SpcColor, const int FillFlag)
{
	VECTOR topPos = { TopPos.x,TopPos.y,TopPos.z };
	VECTOR bottomPos = { BottomPos.x,BottomPos.y,BottomPos.z };

	return DrawCone3D(topPos, bottomPos, r, DivNum, DifColor, SpcColor, FillFlag);
}

int SetCameraPositionAndTargetAndUpVec(
	const Vector3& cameraPosition,		//カメラの位置
	const Vector3& cameraTarget,		//カメラの注視点
	const Vector3& cameraUp				//カメラの上の向き
)
{
	VECTOR position = { cameraPosition.x,cameraPosition.y,cameraPosition.z };
	VECTOR target = { cameraTarget.x, cameraTarget.y, cameraTarget.z };
	VECTOR up = { cameraUp.x,cameraUp.y,cameraUp.z };

	return SetCameraPositionAndTargetAndUpVec(position, target, up);
}

//モデルの座標変換用行列をセット
int MV1SetMatrix(const int MHandle, const Matrix4 Matrix)
{
	MATRIX matrix;
	std::memcpy(&matrix, &Matrix, sizeof MATRIX);	//メモリ間コピー

	return MV1SetMatrix(MHandle, matrix);
}

//x,y,z軸描画
void DrawAxis3D(const float length)
{
	//軸の線
	DrawLine3D(Vector3(-length, 0.0f, 0.0f), Vector3(+length, 0.0f, 0.0f), GetColor(255, 0, 0));//X軸
	DrawLine3D(Vector3(0.0f, -length, 0.0f), Vector3(0.0f, +length, 0.0f), GetColor(0, 255, 0));//Y軸
	DrawLine3D(Vector3(0.0f, 0.0f, -length), Vector3(0.0f, 0.0f, +length), GetColor(0, 0, 255));//Z軸

	//軸の先の描画
	const float ConeSize = 10.0f;

	DrawCone3D(Vector3(length, 0.0f, 0.0f), Vector3(length - ConeSize, 0.0f, 0.0f), ConeSize / 2, 16,
		GetColor(255, 0, 0), GetColor(255, 255, 255), TRUE);

	DrawCone3D(Vector3(0.0f, length, 0.0f), Vector3(0.0f, length - ConeSize, 0.0f), ConeSize / 2, 16,
		GetColor(0, 255, 0), GetColor(255, 255, 255), TRUE);

	DrawCone3D(Vector3(0.0f, 0.0f, length), Vector3(0.0f, 0.0f, length - ConeSize), ConeSize / 2, 16,
		GetColor(0, 0, 255), GetColor(255, 255, 255), TRUE);
}

//キー操作描画
void DrawKeyOperation()
{
	DrawFormatString(10, 20 * 1, GetColor(255, 255, 255), "　[W][E][R]　R : リセット");
	DrawFormatString(10, 20 * 2, GetColor(255, 255, 255), "[A][S][D]　　AD: Y軸周りの回転");
	DrawFormatString(10, 20 * 3, GetColor(255, 255, 255), " [Z]		　　WS: X軸周りの回転");
	DrawFormatString(10, 20 * 4, GetColor(255, 255, 255), "　			EZ: Z軸周りの回転");
}
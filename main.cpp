#include "DxLib.h"
#include "Vector3.h"
#include "Matrix4.h"
#include <cstring>

// ウィンドウのタイトルに表示する文字列
const char TITLE[] = "LE2C_03_イワタ_ユウシロウ";

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
		Vector3(0.0f, 200.0f, -120.0f),//カメラの位置
		Vector3(0.0f, 0.0f, 0.0f),  //カメラの注視点
		Vector3(0.0f, 1.0f, 0.0f)	   //カメラの上の向き
	);

	//時間計測に必要なデータ
	long long startCount = 0;	//開始時間
	long long nowCount = 0;		//現在時間
	long long elapsedCount = 0;	//経過時間

	//補間で使うデータ(start→endを5秒で完了させる)
	Vector3 start(-100.0f, 0.0f, 0.0f);		//スタート地点
	Vector3 point1(-50.0f, 0.0f, 100.0f);		//制御点
	Vector3 point2(50.0f, 0.0f, -100.0f);		//制御点
	Vector3 end(+100.0f, 0.0f, 0.0f);		//ゴール地点
	float	maxTime = 5.0f;					//全体時間
	float	timeRate;						//何パーセント時間が進んだか(率)

	//球の位置
	Vector3 position;

	//実行前にカウンタ値を取得
	startCount = GetNowHiPerformanceCount();

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

		if (CheckHitKey(KEY_INPUT_R))
		{
			startCount = GetNowHiPerformanceCount();
		}
		// 更新処理
		nowCount = GetNowHiPerformanceCount();
		elapsedCount = nowCount - startCount;	//経過時間=現在時間-開始時間
		float elapsedTime = static_cast<float> (elapsedCount) / 1'000'000.0f;//マイクロ秒を秒に単位変換

		//スタート地点		::	start
		//ゴール地点		::	end
		//経過時間			::	elapsedTime[s]
		//移動完了率		::	timeRate(%)

		timeRate = min(elapsedTime / maxTime, 1.0f);

		position = Bezier3(start, point1, point2, end, timeRate);
		// 描画処理
		ClearDrawScreen();
		DrawAxis3D(500.0f);

		//球の描画
		DrawSphere3D(position, 5.0f, 32, GetColor(255, 0, 0), GetColor(255, 255, 255), TRUE);

		//変数の値を表示
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
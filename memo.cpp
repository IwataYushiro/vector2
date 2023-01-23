/*

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
//int MV1SetMatrix(const int MHandle, const Matrix4 Matrix);
//x,y,z軸描画
void DrawAxis3D(const float length);	//x,y,z軸の描画
//キー操作の描画
void DrawKeyOperation();

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

//カメラ座標
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

////モデルの座標変換用行列をセット
//int MV1SetMatrix(const int MHandle, const Matrix4 Matrix)
//{
//	MATRIX matrix;
//	std::memcpy(&matrix, &Matrix, sizeof MATRIX);	//メモリ間コピー
//
//	return MV1SetMatrix(MHandle, matrix);
//}

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

*/
#include <Novice.h>
#include "MathCalc.h"

const char kWindowTitle[] = "学籍番号";

const int kColumnWidth = 60;
const int kRowHeight = 20;

void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* label) {
	Novice::ScreenPrintf(x, y, "%s", label);
	for (int row = 0; row < 4; ++row) {
		for (int column = 0; column < 4; ++column) {
			Novice::ScreenPrintf(
				int(x + column * kColumnWidth), int(y + (row + 1) * kRowHeight), "%6.03f", matrix.m[row][column]
			);
		}
	}
}

void QuaternionPrintf(int x, int y, const Quaternion quaternion, const char* label) {
	Novice::ScreenPrintf(x, y, "%s", label);
	float ray[4] = { quaternion.x,quaternion.y,quaternion.z,quaternion.w };
	for (int column = 0; column < 4; ++column) {
		Novice::ScreenPrintf(int(x + column * kColumnWidth), int(y + kRowHeight), "%6.02f", ray[column]);
	}
}

void VectorScreenPrintf(int x, int y, const Vector3 vector, const char* label) {
	Novice::ScreenPrintf(x, y, "%s", label);
	float ray[3] = { vector.x,vector.y,vector.z };
	for (int column = 0; column < 3; ++column) {
		Novice::ScreenPrintf(int(x + column * kColumnWidth), int(y + kRowHeight), "%6.02f", ray[column]);
	}
}

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	Quaternion rotation =
		QuatLib::MakeRotateAxisAngleQuaternion(MathCalc::Normalize({ 1.0f,0.4f,-0.2f }), 0.45f);
	Vector3 pointY = { 2.1f,-0.9f,1.3f };

	Matrix4x4 rotateMat = MatLib::MakeRotateMatrix(rotation);
	
	Vector3 rotateByQuat = MatLib::RotateVector(pointY, rotation);
	Vector3 rotateByMatrix = MatLib::Transform(pointY, rotateMat);

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///


		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		QuaternionPrintf(0, kRowHeight * 0, rotation, "rotation");

		MatrixScreenPrintf(0, kRowHeight * 3, rotateMat, "matrix");

		VectorScreenPrintf(0, kRowHeight * 9, rotateByQuat, "ByQuat");
		VectorScreenPrintf(0, kRowHeight * 11, rotateByMatrix, "ByMatrix");

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}

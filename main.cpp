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


	Quaternion rotation0 = QuatLib::MakeRotateAxisAngleQuaternion({ 0.71f,0.71f,0.0f }, 0.3f);
	Quaternion rotation1 = QuatLib::MakeRotateAxisAngleQuaternion({ 0.71f,0.0f,0.71f }, 3.141592f);

	Quaternion interpolate0 = QuatLib::Slerp(rotation0, rotation1, 0.0f);
	Quaternion interpolate1 = QuatLib::Slerp(rotation0, rotation1, 0.3f);
	Quaternion interpolate2 = QuatLib::Slerp(rotation0, rotation1, 0.5f);
	Quaternion interpolate3 = QuatLib::Slerp(rotation0, rotation1, 0.7f);
	Quaternion interpolate4 = QuatLib::Slerp(rotation0, rotation1, 1.0f);

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

		QuaternionPrintf(0, kRowHeight * 0, interpolate0, "interpolate0");
		QuaternionPrintf(0, kRowHeight * 2, interpolate1, "interpolate1");
		QuaternionPrintf(0, kRowHeight * 4, interpolate2, "interpolate2");
		QuaternionPrintf(0, kRowHeight * 6, interpolate3, "interpolate3");
		QuaternionPrintf(0, kRowHeight * 8, interpolate4, "interpolate4");

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

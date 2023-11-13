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

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	Vector3 from0 = MathCalc::Normalize(Vector3{ 1.0f,0.7f,0.5f });
	Vector3 to0 = VectorLib::Scaler(from0, -1.0f);
	Vector3 from1 = MathCalc::Normalize(Vector3{ -0.6f,0.9f,0.2f });
	Vector3 to1 = MathCalc::Normalize(Vector3{ 0.4f,0.7f,-0.5f });
	Matrix4x4 rotateMat0 = MatLib::DirectionToDirection(MathCalc::Normalize(Vector3{ 1.0f,0.0f,0.0f }), MathCalc::Normalize(Vector3{ -1.0f,0.0f,0.0f }));
	Matrix4x4 rotateMat1 = MatLib::DirectionToDirection(from0, to0);
	Matrix4x4 rotateMat2 = MatLib::DirectionToDirection(from1, to1);


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

		MatrixScreenPrintf(0, 0, rotateMat0, "rotate0");
		MatrixScreenPrintf(0, kRowHeight * 5, rotateMat1, "rotate1");
		MatrixScreenPrintf(0, kRowHeight * 10, rotateMat2, "rotate2");

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

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

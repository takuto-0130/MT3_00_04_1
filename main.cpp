#include <Novice.h>
#include "Matrix4x4.h"
#include <cmath>
#include <Vector3.h>

//行列の積
Matrix4x4 Multiply(const Matrix4x4& matrix1, const Matrix4x4& matrix2) {
	Matrix4x4 result{};
	float buf;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			buf = 0;
			for (int k = 0; k < 4; k++) {
				buf = buf + matrix1.m[i][k] * matrix2.m[k][j];
				result.m[i][j] = buf;
			}
		}
	}
	return result;
}


//X軸
Matrix4x4 MakeRotateXMatrix(float radian) {
	Matrix4x4 result{};
	result.m[0][0] = 1;
	result.m[3][3] = 1;
	result.m[1][1] = std::cos(radian); result.m[1][2] = std::sin(radian);
	result.m[2][1] = -std::sin(radian); result.m[2][2] = std::cos(radian);
	return result;
}

//Y軸
Matrix4x4 MakeRotateYMatrix(float radian) {
	Matrix4x4 result{};
	result.m[1][1] = 1;
	result.m[3][3] = 1;
	result.m[0][0] = std::cos(radian); result.m[0][2] = -std::sin(radian);
	result.m[2][0] = std::sin(radian); result.m[2][2] = std::cos(radian);
	return result;
}

//Z軸
Matrix4x4 MakeRotateZMatrix(float radian) {
	Matrix4x4 result{};
	result.m[2][2] = 1;
	result.m[3][3] = 1;
	result.m[0][0] = std::cos(radian); result.m[0][1] = std::sin(radian);
	result.m[1][0] = -std::sin(radian); result.m[1][1] = std::cos(radian);
	return result;
}

static const int kRowHeight = 20;
static const int kColumnWidth = 60;


void MatrixScreeenPrintf(int x, int y, Matrix4x4 matrix, const char* text) {
	Novice::ScreenPrintf(x, y, "%s", text);
	for (int row = 0; row < 4; ++row) {
		for (int column = 0; column < 4; ++column) {
			Novice::ScreenPrintf(x + column * kColumnWidth,
				y + (row + 1) * kRowHeight, "%6.2f", matrix.m[row][column]);
		}
	}
}

const char kWindowTitle[] = "LC1A_27_ヤマグチ_タクト_タイトル";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	Vector3 rotate{ 0.4f,1.43f,-0.8f };
	Matrix4x4 rotareXMatrix = MakeRotateXMatrix(rotate.x);
	Matrix4x4 rotareYMatrix = MakeRotateYMatrix(rotate.y);
	Matrix4x4 rotareZMatrix = MakeRotateZMatrix(rotate.z);
	Matrix4x4 rotateXYZMatrix = Multiply(rotareXMatrix, Multiply(rotareYMatrix, rotareZMatrix));

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

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
		
		MatrixScreeenPrintf(0, 0, rotareXMatrix, "rotareXMatrix");
		MatrixScreeenPrintf(0, kRowHeight * 5, rotareYMatrix, "rotareYMatrix");
		MatrixScreeenPrintf(0, kRowHeight * 5 * 2, rotareZMatrix, "rotareZMatrix");
		MatrixScreeenPrintf(0, kRowHeight * 5 * 3, rotateXYZMatrix, "rotateXYZMatrix");

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

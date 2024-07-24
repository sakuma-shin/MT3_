#include <Novice.h>
#define _USE_MATH_DEFINES
#include <cmath>
#include <string.h>
#include <assert.h>
#include "easing.h"
#include"Calculation.h"
#include"Hit.h"
#include"imgui.h"


const int kColmunWidth = 60;
const int kColmunHeight = 50;
const int kWindowWidth = 1280;
const int kWindowHeight = 720;


void VectorScreenPrintf(int x, int y, const Vector3& v, const char* label) {
	Novice::ScreenPrintf(x, y, "%.02f", v.x);
	Novice::ScreenPrintf(x + kColmunWidth, y, "%.02f", v.y);
	Novice::ScreenPrintf(x + kColmunWidth * 2, y, "%.02f", v.z);
	Novice::ScreenPrintf(x + kColmunWidth * 3, y, "%s", label);
}

void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* a) {
	Novice::ScreenPrintf(x, y, "%s", a);
	for (int row = 0; row < 4; ++row) {
		for (int column = 0; column < 4; ++column) {
			Novice::ScreenPrintf(
				x + (column + 1) * kColmunWidth, y + (row + 1) * kColmunHeight, "%0.02f", matrix.m[row][column]);
		}
	}
}

const char kWindowTitle[] = "LE2D_07_サクマ_シン_タイトル";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	Vector3 cameraRotate = { 0.26f,0.0f,0.0f };
	Vector3 cameraTranslate = { 0.0f,1.9f,-6.49f };

	Plane plane;
	plane.normal = { 0.0f,0.0f,1.0f };
	plane.distance = 5.0f;

	Segment segment;
	segment.origin = { 0.0f,0.0f,1.0f };
	segment.diff = { 1.0f,1.0f,1.0f };


	uint32_t color = BLACK;

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
		ImGui::Begin("Window");
		ImGui::DragFloat3("cameraTranslate", &cameraTranslate.x, 0.01f);
		ImGui::DragFloat3("CameraRotate", &cameraRotate.x, 0.01f);
		ImGui::DragFloat3("segmentDiff", &segment.diff.x, 0.01f);
		ImGui::DragFloat("segmentOrigin", &segment.origin.x, 0.01f);
		ImGui::DragFloat3("Plane.Normal", &plane.normal.x, 0.01f);
		ImGui::End();

		plane.normal = Normalize(plane.normal);
		
		Matrix4x4 cameraMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, cameraRotate, cameraTranslate);
		Matrix4x4 viewMatrix = Inverse(cameraMatrix);
		Matrix4x4 projectionMatrix = MakePerspectiveFovMatrix(0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f);
		////WVPMatrixを作る
		//Matrix4x4 worldViewProjectionMatrix = Multiply(cameraMatrix, Multiply(viewMatrix, projectionMatrix));
		// 
		Matrix4x4 viewProjectionMatrix = Multiply(viewMatrix, projectionMatrix);
		// 
		//viewportMatrixを作る
		Matrix4x4 viewportMatrix = MakeViewportMatrix(0, 0, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);

		Vector3 start = TransForm(TransForm(segment.origin, viewProjectionMatrix), viewportMatrix);
		Vector3 end = TransForm(TransForm(Add(segment.origin, segment.diff), viewProjectionMatrix), viewportMatrix);

		if (IsCollision(segment, plane)) {
			color = RED;
		} else {
			color = BLACK;
		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから

		DrawGrid(viewProjectionMatrix, viewportMatrix);
		
		DrawPlane(plane, viewProjectionMatrix, viewportMatrix, color);

		Novice::DrawLine(int(start.x), int(start.y), int(end.x), int(end.y), color);
		
		

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

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
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	Vector3 cameraRotate = { 0.26f,0.0f,0.0f };
	Vector3 cameraTranslate = { 0.0f,1.9f,-6.49f };

	Vector3 translates[3];
	translates[0] = { 0.2f,1.0f,0.0f };
	translates[1] = { 0.4f,0.0f,0.0f };
	translates[2] = { 0.3f,0.0f,0.0f };

	Vector3 rotates[3];
	rotates[0] = { 0.0f,0.0f,-6.8f };
	rotates[1] = { 0.0f,0.0f,-1.4f };
	rotates[2] = { 0.0f,0.0f,0.0f };

	Vector3 scales[3];
	scales[0] = { 1.0f,1.0f,1.0f };
	scales[1] = { 1.0f,1.0f,1.0f };
	scales[2] = { 1.0f,1.0f,1.0f };

	Sphere sphere1;
	sphere1.center =translates[0];
	sphere1.radius = 0.075f;

	Sphere sphere2;
	sphere2.center = translates[1];
	sphere2.radius = 0.075f;

	Sphere sphere3;
	sphere3.center = translates[2];
	sphere3.radius = 0.075f;

	Segment shoulderToElbow;
	shoulderToElbow.origin = {};
	shoulderToElbow.diff = {};

	Segment elbowToHand;
	elbowToHand.origin = {};
	elbowToHand.diff = {};





	/*uint32_t color = BLACK;*/

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
		ImGui::DragFloat3("translates[0]", &translates[0].x, 0.01f);
		ImGui::DragFloat3("translates[1]", &translates[1].x, 0.01f);
		ImGui::DragFloat3("translates[2]", &translates[2].x, 0.01f);
		/*ImGui::DragFloat3("segmentOrigin", &segment.origin.x, 0.01f);*/

		/*ImGui::DragFloat3("SphereCenter", &sphere.center.x, 0.01f);
		ImGui::DragFloat("SphereRadius", &sphere.radius, 0.01f);*/
		/*	ImGui::DragFloat3("aabb2.min", &aabb2.min.x, 0.01f);
			ImGui::DragFloat3("aabb2.max", &aabb2.max.x, 0.01f);*/

		ImGui::End();


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

		Vector3 shoulderPos = TransForm(TransForm(translates[0], viewProjectionMatrix), viewportMatrix);
		shoulderToElbow.origin = shoulderPos;

		Vector3 elbowPos= TransForm(TransForm(translates[1], viewProjectionMatrix), viewportMatrix);
		shoulderToElbow.diff = Subtract(elbowPos, shoulderPos);
		elbowToHand.origin = elbowPos;
		
		Vector3 handPos= TransForm(TransForm(translates[2], viewProjectionMatrix), viewportMatrix);
		elbowToHand.diff = Subtract(handPos, elbowPos);

		Vector3 shoulderToElbowEnd = Add(shoulderToElbow.origin, shoulderToElbow.diff);

		Vector3 elbowToHandEnd = Add(elbowToHand.origin, elbowToHand.diff);

		sphere1.center = translates[0];

		sphere2.center = translates[1];

		sphere3.center = translates[2];

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから

		DrawGrid(viewProjectionMatrix, viewportMatrix);


		/*DrawTriangle(triangle, viewProjectionMatrix, viewportMatrix,color);*/

		Novice::DrawLine(int(shoulderToElbow.origin.x), int(shoulderToElbow.origin.y), int(shoulderToElbowEnd.x), int(shoulderToElbowEnd.y), WHITE);

		Novice::DrawLine(int(elbowToHand.origin.x), int(elbowToHand.origin.y), int(elbowToHandEnd.x), int(elbowToHandEnd.y), WHITE);

		DrawSphere(sphere1, viewProjectionMatrix, viewportMatrix, RED);
		DrawSphere(sphere2, viewProjectionMatrix, viewportMatrix, GREEN);
		DrawSphere(sphere3, viewProjectionMatrix, viewportMatrix, BLUE);



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

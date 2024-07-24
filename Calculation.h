#pragma once
#include <Novice.h>
#define _USE_MATH_DEFINES
#include <cmath>
#include"Vector3.h"
#include"Matrix4x4.h"
#include<algorithm>

struct Sphere {
	Vector3 center;
	float radius;
};

struct Line {
	Vector3 origin;
	Vector3 diff;
};

struct Ray {
	Vector3 origin;
	Vector3 diff;
};

struct Segment {
	Vector3 origin;
	Vector3 diff;
};

struct Plane {
	Vector3 normal;// 法線
	float distance;//距離
};

struct Triangle {
	Vector3 vertices[3];//頂点
};

struct AABB {
	Vector3 min;//最小点
	Vector3 max;//最小点

};

//加算
Vector3 Add(const Vector3& v1, const Vector3& v2);

//減算
Vector3 Subtract(const Vector3& v1, const Vector3& v2);

//スカラー倍
Vector3 Multiply(float scalar, const Vector3& v);

//内積
float Dot(const Vector3& v1, const Vector3& v2);


//長さ
float Length(const Vector3& v);

//正規化
Vector3 Normalize(const Vector3& v);



//加算
Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2);

//減算
Matrix4x4 Subtract(const Matrix4x4& m1, const Matrix4x4& m2);

//積
Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);

Matrix4x4 Inverse(const Matrix4x4& m);
//転置行列
Matrix4x4 Transpose(const Matrix4x4& m);

//単位行列を作成
Matrix4x4 MakeIdentity4x4();



//平行移動行列
Matrix4x4 MakeTraslateMatrix(const Vector3& translate);

//拡大縮小行列
Matrix4x4 MakeScaleMatrix(const Vector3& scale);


//座標変換
Vector3 TransForm(const Vector3& vector3, const Matrix4x4& matrix);

//1.X軸回転行列
Matrix4x4 MakeRotateXMatrix(float radian);

//2.Y軸回転行列
Matrix4x4 MakeRotateYMatrix(float radian);

//3.Z軸回転行列
Matrix4x4 MakeRotateZMatrix(float radian);

//回転行列の合成
Matrix4x4 RotateXYZMatrix(const Vector3& radian);

//3次元アフィン変換行列
Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate);

//1.透視射影行列
Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip);

//2.正射影行列
Matrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip);

//3.ビューポート変換行列
Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth);

//クロス積
Vector3 Cross(const Vector3& v1, const Vector3& v2);

void DrawGrid(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewPortMatrix);

void DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, Matrix4x4& viewportMatrix, uint32_t color);


Vector3 Project(const Vector3& v1, const Vector3& v2);

Vector3 ClosestPoint(const Vector3& point, const Segment& segment);

// 平面の頂点を計算する関数
Vector3 Perpendicular(const Vector3& normal);


void DrawPlane(const Plane& plane, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);

void DrawTriangle(const Triangle& triangle, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);

void DrawAABB(const AABB& aabb, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);

void Lerp(const Vector3& v1, const Vector3& v2, float t);

void DrawBezier(const Vector3& controlPoint0, const Vector3& controlPoint1, const Vector3& controlPoint2,
	const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewPortMatrix, uint32_t color);
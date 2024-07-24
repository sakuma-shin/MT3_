#include"Hit.h"

int HitBox(Corners a, Corners b) {
	if (b.leftTop.x <= a.rightTop.x && a.leftTop.x < b.rightTop.x) {
		if (b.leftTop.y <= a.rightDown.y && a.leftTop.y < b.rightDown.y) {
			return 1;
		} else {
			return 0;
		}
	} else {
		return 0;
	}
}

int HitCircle(Vector2 circle1pos, float circle1radius, Vector2 circle2pos, float circle2radius) {
	Vector2 distance;
	float center2center;
	distance.x = circle2pos.x - circle1pos.x;
	distance.y = circle2pos.y - circle1pos.y;

	center2center = sqrtf(distance.x * distance.x + distance.y * distance.y);

	if (center2center <= circle1radius + circle2radius) {
		return 1;
	} else {
		return 0;
	}
}

int inclusionCircle(Vector2 circle1pos, float circle1radius, Vector2 circle2pos, float circle2radius) {
	Vector2 distance;
	float center2center;
	distance.x = circle2pos.x - circle1pos.x;
	distance.y = circle2pos.y - circle1pos.y;

	center2center = sqrtf(distance.x * distance.x + distance.y * distance.y);

	float circleDifference = circle1radius - circle2radius;
	if (circleDifference < 0) {
		circleDifference *= -1;
	}

	if (center2center <= circleDifference) {
		return 1;
	} else {
		return 0;
	}
}

bool IsCollision(const Sphere& sphere, const Plane& plane) {
	// 球の中心から平面までの距離を計算
	float distance = (plane.normal.x * sphere.center.x +
		plane.normal.y * sphere.center.y +
		plane.normal.z * sphere.center.z - plane.distance);

	// 球の半径以下なら衝突している
	return std::abs(distance) <= sphere.radius;
}

bool IsCollision(const Segment& segment, const Plane& plane)
{
	// セグメントの開始点
	Vector3 P0 = segment.origin;
	// セグメントの終点
	Vector3 P1 = Add(segment.origin, segment.diff);

	// 平面の法線ベクトル
	Vector3 n = plane.normal;
	// 平面上の点（法線ベクトルのスケールとして平面の距離を使用）
	Vector3 P = Multiply(plane.distance, Normalize(plane.normal));

	// P0 と P1 の平面からの距離を計算
	float d0 = Dot(n, Subtract(P0, P));
	float d1 = Dot(n, Subtract(P1, P));

	// 符号が異なる場合、セグメントは平面と交差する
	if (d0 * d1 <= 0) {
		return true;
	} else {
		return false;
	}
}

bool IsCollision(const Segment& segment, const Triangle& triangle)
{
	//三角形の法線
	Vector3 edge1 = Subtract(triangle.vertices[1], triangle.vertices[0]);
	Vector3 edge2 = Subtract(triangle.vertices[2], triangle.vertices[0]);
	Vector3 normal = Normalize(Cross(edge1, edge2));

	// 法線ベクトルと距離から平面の方程式を求める
	float distance = Dot(normal, triangle.vertices[0]);

	Plane trianglePlane = { normal,distance };
	if (!IsCollision(segment, trianglePlane)) {
		return false;
	} else {

		//交差点を計算
		Vector3 direction = Normalize(segment.diff);
		float t = (distance - Dot(normal, segment.origin)) / Dot(normal, direction);
		Vector3 intersection = Add(segment.origin, Multiply(t, direction));

		//各辺の差分ベクトル
		Vector3 v01 = Subtract(triangle.vertices[1], triangle.vertices[0]);
		Vector3 v12 = Subtract(triangle.vertices[2], triangle.vertices[1]);
		Vector3 v20 = Subtract(triangle.vertices[0], triangle.vertices[2]);

		//頂点と衝突点を結んだベクトル
		Vector3 v0p = Subtract(intersection, triangle.vertices[0]);
		Vector3 v1p = Subtract(intersection, triangle.vertices[1]);
		Vector3 v2p = Subtract(intersection, triangle.vertices[2]);

		//各辺を結んだベクトルと、頂点と衝突点pを結んだベクトルのクロス積を取る
		Vector3 cross01 = Cross(v01, v1p);
		Vector3 cross12 = Cross(v12, v2p);
		Vector3 cross20 = Cross(v20, v0p);

		if (Dot(cross01, normal) >= 0.0f &&
			Dot(cross12, normal) >= 0.0f &&
			Dot(cross20, normal) >= 0.0f) {
			return true;
		} else {
			false;
		}
		return false;
	}
}

bool IsCollision(const AABB& a, const AABB& b)
{
	if (a.min.x <= b.max.x && a.max.x >= b.min.x &&
		a.min.y <= b.max.y && a.max.y >= b.min.y &&
		a.min.z <= b.max.z && a.max.z >= b.min.z) {
		return true;
	} else {
		return false;
	}

}

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
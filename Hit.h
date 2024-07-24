#pragma once
#include <Novice.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include"Vector2.h"
#include"Calculation.h"


struct Corners {
Vector2 leftTop;
Vector2 rightTop;
Vector2 leftDown;
Vector2 rightDown;
};

int HitBox(Corners a, Corners b);

int HitCircle(Vector2 circle1pos, float circle1radius, Vector2 circle2pos, float circle2radius);

int inclusionCircle(Vector2 circle1pos, float circle1radius, Vector2 circle2pos, float circle2radius);

bool IsCollision(const Sphere& sphere, const Plane& plane);

bool IsCollision(const Segment& segment, const Plane& plane);

bool IsCollision(const Segment& segment, const Triangle& triangle);

bool IsCollision(const AABB& a, const AABB& b);

bool IsCollision(const AABB& aabb, const Sphere& sphere);

bool IsCollision(const AABB& aabb, Segment& segment);
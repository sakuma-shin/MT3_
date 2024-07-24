#pragma once
#include <Novice.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include"Vector2.h"


struct Corners {
Vector2 leftTop;
Vector2 rightTop;
Vector2 leftDown;
Vector2 rightDown;
};

int HitBox(Corners a, Corners b);

int HitCircle(Vector2 circle1pos, float circle1radius, Vector2 circle2pos, float circle2radius);

int inclusionCircle(Vector2 circle1pos, float circle1radius, Vector2 circle2pos, float circle2radius);
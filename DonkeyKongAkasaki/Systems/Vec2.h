#pragma once
#include <cmath>

// 矩形の当たり判定
struct Rect
{
	float left;
	float top;
	float right;
	float bottom;
};

class Vec2
{
public:
	float x;
	float y;

public:
	Vec2() :
		x(0.0f),
		y(0.0f)
	{
	}
	Vec2(float posX, float posY) :
		x(posX),
		y(posY)
	{
	}
	// 単項演算子+  Vec = +Vec2
	Vec2 operator+() const
	{
		return *this;
	}
	// 単項演算子-  Vec = -Vec2
	Vec2 operator-() const
	{
		return Vec2{ -x,-y };
	}

	// 足し算
	Vec2 operator+(Vec2 vec) const
	{
		return Vec2{ x + vec.x,y + vec.y };
	}
	// Vec2 += Vec2
	Vec2 operator+=(Vec2 vec)
	{
		x += vec.x;
		y += vec.y;
		return *this;
	}
};


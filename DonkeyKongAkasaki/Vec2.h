#pragma once
#include <cmath>
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
	// ’P€‰‰Zq+  Vec = +Vec2
	Vec2 operator+() const
	{
		return *this;
	}
	// ’P€‰‰Zq-  Vec = -Vec2
	Vec2 operator-() const
	{
		return Vec2{ -x,-y };
	}

	// ‘«‚µZ
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


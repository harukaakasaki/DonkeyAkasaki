#pragma once
#include"Vec2.h"

class Player;
class Camera
{
public:
	Camera();
	~Camera();
	void Init();
	void Update(Player& player);
	// ‰æ–Ê‚ð—h‚ç‚·
	void Shake(int frame, float power);

	Vec2 GetPos() const{ return m_pos+drawOffset; };

private:
	Vec2 m_pos;
	Vec2 drawOffset;

	int m_shakeFrame = 0;
	float m_shakePower = 0.0f;
};




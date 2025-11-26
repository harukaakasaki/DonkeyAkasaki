#pragma once
#include "Enemy.h"
class EnemyBat :public Enemy
{
public:
	EnemyBat();
	~EnemyBat();
	void Init() override;
	void Update()override;
	void Draw(const Camera& camera)override;

private:
	Vec2 m_pos;
	float m_speed = 2.0f;
};


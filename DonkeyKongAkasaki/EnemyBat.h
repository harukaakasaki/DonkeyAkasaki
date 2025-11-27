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
	// Batの位置
	Vec2 m_pos;
	// アニメーションのフレーム数
	int m_animFrame = 0;
};


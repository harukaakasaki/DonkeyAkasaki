#pragma once
#include "Enemy.h"
class EnemyMush :public Enemy
{
public:
	EnemyMush();
	~EnemyMush();
	void Init() override;
	void Update()override;
	void Draw(const Camera& camera)override;

	Rect EnemyMushHitBox()const;

private:

	// アニメーションのフレーム数
	int m_animFrame = 0;
	// コマ送りのカウンタ
	int m_animCount = 0;
	// キノコの移動時間
	int m_moveTimer = 0;
	// 左に動いているか
	bool m_moveLeft = false;

	int m_normalAnim[9]; // 通常コマ数
	//int attackAnim[10];// 攻撃コマ数
	//int moveAnim[8];   // 移動コマ数

};


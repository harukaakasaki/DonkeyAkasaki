#pragma once
#include "Enemy.h"
class EnemyMush :public Enemy
{
	enum class MushState
	{
		Normal,
		Damage,
		Death,
		DeathEffect,
	};
public:
	EnemyMush();
	~EnemyMush();
	void Init() override;
	void Update()override;
	void Draw(const Camera& camera)override;

	void Damage(); // ダメージ

	Rect EnemyMushHitBox()const;

private:

	void UpdateState();// アニメーション更新

	MushState m_state = MushState::Normal;// キノコの通常状態

	// アニメーションのフレーム数
	int m_animFrame = 0;
	// コマ送りのカウンタ
	int m_animCount = 0;
	// キノコの移動時間
	int m_moveTimer = 0;
	// 左に動いているか
	bool m_moveLeft = false;
	// キノコのHP
	int m_hp;
	// 無敵時間
	int m_damageCoolTime = 0;
	// 攻撃されたら止まる
	int m_stopTimer = 0;

};


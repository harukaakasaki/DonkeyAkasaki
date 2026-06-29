#pragma once
#include "Enemy.h"
class EnemyGolem :public Enemy
{
	enum class GolemState
	{
		Normal,
		Damage,
		Death,
		DeathEffect
	};
public:
	EnemyGolem();
	~EnemyGolem();
	void Init() override;
	void Update()override;
	void Draw(const Camera& camera)override;

	void Damage(); // ダメージ

	Rect EnemyGolemHitBox()const;

private:

	// アニメーション更新
	void UpdateState();

	GolemState m_state = GolemState::Normal;// ゴーレムの通常状態

	// アニメーションのフレーム数
	int m_animFrame = 0;
	// コマ送りのカウンタ
	int m_animCount = 0;
	// ゴーレムの移動時間
	int m_moveTimer = 0;
	// 左に動いているか
	bool m_moveLeft = false;
	// ゴーレムのHP
	int m_hp;
	// 無敵時間
	int m_damageCoolTime = 0;
	// 攻撃されたら止まる
	int m_stopTimer = 0;
	// SE系
	int m_hitSe;
	int m_deathSe;
	int m_effectSe;

};


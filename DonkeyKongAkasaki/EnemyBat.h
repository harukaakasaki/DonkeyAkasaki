#pragma once
#include "Enemy.h"
class EnemyBat :public Enemy
{
	enum class BatState
	{
		Normal,
		Death,
		DeathEffect,
	};

public:
	EnemyBat();
	~EnemyBat();
	void Init() override;
	void Update()override;
	void Draw(const Camera& camera)override;
	
	void Damage(); // ダメージ

	

	Rect EnemyBatHitBox()const;

private:

	void UpdateState();// アニメーション更新

	BatState m_state = BatState::Normal;// コウモリの通常状態

	// アニメーションのフレーム数
	int m_animFrame = 0;
	// コマ送りのカウンタ
	int m_animCount = 0;
	// コウモリの移動時間
	int m_moveTimer = 0;
	// 左に動いているか
	bool m_moveLeft = false;
	// コウモリのHP
	int m_hp = 1;
	// SE系
	int m_hitSe;
	int m_effectSe;

};


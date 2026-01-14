#include "EnemyGolem.h"
#include "Character.h"
#include <DxLib.h>

namespace
{
	constexpr int kIdleAnimNum = 8;                  // プレイヤーのIdleアニメーション
	constexpr int kAnimWaitFrame = 1;                // ↑ 1コマ当たりのフレーム数
	constexpr int kGraphicsAngle = 0;                // グラフィックアングル
	constexpr int kGraphWidth = 80; // プレイヤーのグラフィックサイズ（幅）
	constexpr int kGraphHeight = 64;                // プレイヤーのグラフィックサイズ（高さ）
	constexpr int kSpeed = 3;                        // ゴーレムのスピード
	constexpr float kGraphicsSize = 3.0f;            // グラフィックサイズ
}

EnemyGolem::EnemyGolem():
	m_animFrame(0),
	m_animCount(0),
	m_normalAnim(0)
{
	m_handle = LoadGraph("data/Golem.png");
	m_hp = 3;
}

EnemyGolem::~EnemyGolem()
{
	DeleteGraph(m_handle);
}

void EnemyGolem::Init()
{
	m_state = GolemState::Normal;
	m_pos = { 300.0f,545.0f };
	m_isAlive = true;
}

void EnemyGolem::Update()
{
	UpdateState();

	Character::Update();

	if (m_stopTimer > 0)
	{
		m_stopTimer--;
		return;
	}


	m_moveTimer++;
	if (m_moveTimer >= 300)
	{
		m_moveLeft = !m_moveLeft;
		m_moveTimer = 0;
	}
	if (m_moveLeft)
	{
		m_pos.x -= 4;
	}
	else
	{
		m_pos.x += 4;
	}

	if (m_damageCoolTime > 0)
	{
		m_damageCoolTime--;
	}

}

void EnemyGolem::UpdateState()
{
	m_animCount++;

	if (m_animCount > 2)// アニメーションスピード
	{
		m_animCount = 0;// はじめに戻す
		m_animFrame++;  // 次のコマへ
	}

	if (m_state == GolemState::Normal)
	{
		if (m_animFrame >= 9)// 通常 = 7
		{
			m_animFrame = 0;

		}
	}

	if (m_state == GolemState::Damage)
	{
		if (m_animFrame >= 3)// ヒット = 3
		{
			m_state = GolemState::Normal;
			m_animFrame = 0;

		}
	}

	if (m_state == GolemState::Death)
	{
		if (m_animFrame >= 3)// ヒット = 3
		{
			m_state = GolemState::Normal;
			m_animFrame = 0;

		}
	}
}


void EnemyGolem::Damage()
{
	m_state = GolemState::Damage;

	if (m_damageCoolTime > 0)
	{
		return;
	}

	m_hp--;

	// 止まる
	m_stopTimer = 30;

	// 無敵時間
	m_damageCoolTime = 30;


	if (m_hp <= 0)
	{
		m_state = GolemState::Death;
		Kill();
	}
}

void EnemyGolem::Draw(const Camera& camera)
{
	// ゴーレムが死んでいたら何もしない
	if (!m_isAlive)return;

	Vec2 cam = camera.GetPos();

	// アニメーションのフレーム数から表示したいコマ番号
	int animNo = m_animFrame;
	// アニメーションの進行に合わせてグラフィックを切り取る
	int srcX = kGraphWidth * animNo;
	int srcY = 0;

	int w = kGraphWidth * kGraphicsSize;
	int h = kGraphHeight * kGraphicsSize;

	if (m_state == GolemState::Normal)
	{
		DrawRectRotaGraph(static_cast<int>(m_pos.x - cam.x),
			static_cast<int>(m_pos.y - cam.y),//-35は地面への位置調整
			srcX, srcY,
			kGraphWidth, kGraphHeight, kGraphicsSize, kGraphicsAngle,
			m_handle, true);
	}
	
#ifdef _DEBUG
	// 当たり判定（ゴーレム）の描画
	DrawBox(static_cast<int>(m_pos.x - cam.x - w / 3),
		static_cast<int>(m_pos.y - cam.y - 35 - h / 10),
		static_cast<int>(m_pos.x - cam.x + w / 3),
		static_cast<int>(m_pos.y - cam.y - 35 + h / 3),
		GetColor(255, 0, 0), false);
#endif // DEBUG
}



Rect EnemyGolem::EnemyGolemHitBox() const
{
	if (m_state == GolemState::Death)
	{
		return Rect{ 0,0,0,0 };
	}

	float w = kGraphWidth * kGraphicsSize;
	float h = kGraphHeight * kGraphicsSize;

	Rect r;
	r.left = m_pos.x - w / 3;
	r.top = m_pos.y - 35 - h / 10;
	r.right = m_pos.x + w / 3;
	r.bottom = m_pos.y - 35 + h / 3;

	return r;
}

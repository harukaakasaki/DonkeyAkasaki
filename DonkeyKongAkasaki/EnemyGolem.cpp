#include "EnemyGolem.h"
#include "Character.h"
#include <DxLib.h>

namespace
{
	constexpr int kIdleAnimNum = 8;                  // プレイヤーのIdleアニメーション
	constexpr int kAnimWaitFrame = 1;                // ↑ 1コマ当たりのフレーム数
	constexpr int kGraphicsAngle = 0;                // グラフィックアングル
	constexpr int kGraphWidth = 90;					 // プレイヤーのグラフィックサイズ（幅）
	constexpr int kGraphHeight = 64;                 // プレイヤーのグラフィックサイズ（高さ）
	constexpr int kEffectWidth = 64;                 // ゴーレムのエフェクトサイズ（幅）
	constexpr int kEffectHeight = 64;                // ゴーレムのエフェクトサイズ（高さ）
	constexpr int kSpeed = 3;                        // ゴーレムのスピード
	constexpr float kGraphicsSize = 12.0f;            // グラフィックサイズ
	constexpr float kEffectSize = 14.0f;              // エフェクトサイズ
}

EnemyGolem::EnemyGolem():
	m_animFrame(0),
	m_animCount(0)
{
	// 画像
	m_handle = LoadGraph("data/golem_run.png");
	m_hitHandle = LoadGraph("data/golem_hit2.png");
	m_deathHandle = LoadGraph("data/golem_death2.png");
	m_effectHandle = LoadGraph("data/explosion2.png");
	// SE
	m_hitSe = LoadSoundMem("bgm/golem_hit_se.mp3");
	m_deathSe = LoadSoundMem("bgm/golem_death_se.mp3");
	m_effectSe = LoadSoundMem("bgm/boom_se.mp3");
	m_hp = 10;
}

EnemyGolem::~EnemyGolem()
{
	DeleteGraph(m_handle);
	DeleteGraph(m_hitHandle);
	DeleteGraph(m_deathHandle);
	DeleteGraph(m_effectHandle);
	DeleteSoundMem(m_hitSe);
	DeleteSoundMem(m_deathSe);
	DeleteSoundMem(m_effectSe);
}

void EnemyGolem::Init()
{
	m_state = GolemState::Normal;
	m_pos = { 300.0f,545.0f };
	m_isAlive = true;
}

void EnemyGolem::Update()
{
	// 状態の更新
	UpdateState();

	if (!m_isAlive)return;

	if (m_state == GolemState::Death)return;
	if (m_state == GolemState::DeathEffect)return;

	Character::Update();

	if (m_stopTimer > 0)
	{
		m_stopTimer--;
		return;
	}


	m_moveTimer++;
	if (m_moveTimer >= 420)
	{
		m_moveLeft = !m_moveLeft;
		m_moveTimer = 0;
	}
	if (m_moveLeft)
	{
		m_pos.x -= kSpeed;
		m_isRight = false;
	}
	else
	{
		m_pos.x += kSpeed;
		m_isRight = true;
	}

	if (m_damageCoolTime > 0)
	{
		m_damageCoolTime--;
	}

}

void EnemyGolem::UpdateState()
{
	m_animCount++;

	if (m_animCount > 4)// アニメーションスピード
	{
		m_animCount = 0;// はじめに戻す
		m_animFrame++;  // 次のコマへ
	}

	if (m_state == GolemState::Normal)
	{
		if (m_animFrame >= 10)// 通常 = 7
		{
			m_animFrame = 0;

		}
	}

	if (m_state == GolemState::Damage)
	{
		if (m_animFrame >= 4)// ヒット = 4
		{
			
			m_state = GolemState::Normal;
			m_animFrame = 0;

		}
	}

	if (m_state == GolemState::Death)
	{
		if (m_animFrame >= 11)// 死 = 11
		{
			PlaySoundMem(m_effectSe, DX_PLAYTYPE_BACK);
			m_state = GolemState::DeathEffect;
			m_animFrame = 0;

		}
	}
	if (m_state == GolemState::DeathEffect)
	{
		if (m_animFrame >= 12)// 死エフェクト = 12
		{
			Kill();
			m_animFrame = 0;

		}
	}
}


void EnemyGolem::Damage()
{
	if (m_damageCoolTime > 0)
	{
		return;
	}
	PlaySoundMem(m_hitSe, DX_PLAYTYPE_BACK);
	m_state = GolemState::Damage;
	m_animFrame = 0;
	m_animCount = 0;

	m_hp--;

	// 止まる
	m_stopTimer = 10;

	// 無敵時間
	m_damageCoolTime = 30;


	if (m_hp <= 0)
	{
		PlaySoundMem(m_deathSe, DX_PLAYTYPE_BACK);
		m_state = GolemState::Death;
		m_animFrame = 0;
		m_animCount = 0;
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
			m_handle, true, !m_isRight);
	}

	if (m_state == GolemState::Damage)
	{
		DrawRectRotaGraph(static_cast<int>(m_pos.x - cam.x),
			static_cast<int>(m_pos.y - cam.y),//-35は地面への位置調整
			srcX, srcY,
			kGraphWidth, kGraphHeight, kGraphicsSize, kGraphicsAngle,
			m_hitHandle, true, !m_isRight);
	}


	if (m_state == GolemState::Death)
	{
		DrawRectRotaGraph(static_cast<int>(m_pos.x - cam.x),
			static_cast<int>(m_pos.y - cam.y),//-35は地面への位置調整
			srcX, srcY,
			kGraphWidth, kGraphHeight, kGraphicsSize, kGraphicsAngle,
			m_deathHandle, true, !m_isRight);
	}

	if (m_state == GolemState::DeathEffect)
	{
		int effectSrcX = kEffectWidth * m_animFrame;
		int effectSrcY = 0;
		DrawRectRotaGraph(static_cast<int>(m_pos.x - cam.x),
			static_cast<int>(m_pos.y - cam.y),//-35は地面への位置調整
			effectSrcX, effectSrcY,
			kEffectWidth, kEffectHeight, kEffectSize, kGraphicsAngle,
			m_effectHandle, true, !m_isRight);
	}
	
#ifdef _DEBUG
	// 当たり判定（ゴーレム）の描画
	DrawBox(static_cast<int>(m_pos.x - cam.x - w / 5),
		static_cast<int>(m_pos.y - cam.y - 5 - h / 10),
		static_cast<int>(m_pos.x - cam.x + w / 5),
		static_cast<int>(m_pos.y - cam.y - 5 + h / 2),
		GetColor(255, 0, 0), false);
#endif // DEBUG
}



Rect EnemyGolem::EnemyGolemHitBox() const
{
	if (m_state == GolemState::Death||m_state == GolemState::DeathEffect)
	{
		return Rect{ 0,0,0,0 };
	}

	float w = kGraphWidth * kGraphicsSize;
	float h = kGraphHeight * kGraphicsSize;

	Rect r;
	r.left = m_pos.x - w / 5;
	r.top = m_pos.y - 5 - h / 10;
	r.right = m_pos.x + w / 5;
	r.bottom = m_pos.y - 5 + h / 2;

	return r;
}

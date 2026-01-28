#include "EnemyMush.h"
#include "Character.h"
#include <DxLib.h>


namespace
{
	constexpr int kIdleAnimNum      = 7;    // キノコのIdleアニメーション
	constexpr int kAnimWaitFrame    = 1;    // ↑ 1コマ当たりのフレーム数
	constexpr int kGraphicsAngle    = 0;    // グラフィックアングル
	constexpr int kGraphWidth       = 80;   // キノコのグラフィックサイズ（幅）
	constexpr int kGraphHeight      = 64;   // キノコのグラフィックサイズ（高さ）
	constexpr int kEffectWidth      = 64;   // キノコのエフェクトサイズ（幅）
	constexpr int kEffectHeight     = 64;   // キノコのエフェクトサイズ（高さ）
	constexpr int kAnimSpeed        = 3;    // キノコのアニメーションスピード
	constexpr int kSpeed            = 3;    // キノコのスピード
	constexpr int kMoveTime         = 60;   // キノコの移動時間
	constexpr float kGraphicsSize   = 3.0f; // グラフィックサイズ
	constexpr float kEffectSize     = 4.0f; // エフェクトサイズ
	constexpr float kNormalFrame    = 8.0f; // 通常アニメーションフレーム
	constexpr float kDamageFrame    = 5.0f; // ダメージアニメーションフレーム
	constexpr float kDeathFrame     = 15.0f;// 死アニメーションフレーム
	constexpr float kEffectFrame    = 11.0f;// エフェクトアニメーションフレーム
	constexpr float kStopTime       = 30.0f;// 停止時間
	constexpr float kDamageCoolTime = 1.0f; // ダメージクールタイム

}

EnemyMush::EnemyMush():
	m_animFrame(0),
	m_animCount(0)
{
	// 画像
	m_handle = LoadGraph("data/mush_run.png");         // 通常画像
	m_hitHandle = LoadGraph("data/mush_hit2.png");     // ヒット画像
	m_deathHandle = LoadGraph("data/mush_death2.png"); // 死画像
	m_effectHandle = LoadGraph("data/explosion3.png"); // エフェクト画像
	// SE
	m_hitSe = LoadSoundMem("bgm/enemy_hit_se.mp3");    // ヒットSE
	m_deathSe = LoadSoundMem("bgm/enemy_death_se.mp3");// 死SE
	m_effectSe = LoadSoundMem("bgm/boom_se.mp3");      // エフェクトSE
	
}

EnemyMush::~EnemyMush()
{
	DeleteGraph(m_handle);
	DeleteGraph(m_hitHandle);
	DeleteGraph(m_deathHandle);
	DeleteGraph(m_effectHandle);
	DeleteSoundMem(m_hitSe);
	DeleteSoundMem(m_deathSe);
	DeleteSoundMem(m_effectSe);
}

void EnemyMush::Init()
{
	// HP
	m_hp = 2;
	m_state = MushState::Normal;
	m_pos = { 500.0f,545.0f };
	m_isAlive = true;
}

void EnemyMush::Update()
{
	// 状態の更新
	UpdateState();

	if (!m_isAlive)return;

	if (m_state == MushState::Death)return;
	if (m_state == MushState::DeathEffect)return;

	Character::Update();

	if (m_stopTimer > 0)
	{
		m_stopTimer--;
		return;
	}

	m_moveTimer++;
	if (m_moveTimer >= kMoveTime)
	{
		m_moveLeft = !m_moveLeft;
		m_moveTimer = 0;
	}
	if (m_moveLeft)
	{
		m_pos.x -= kSpeed;
		m_isRight = true;
	}
	else
	{
		m_pos.x += kSpeed;
		m_isRight = false;
	}

	if (m_damageCoolTime > 0)
	{
		m_damageCoolTime--;
	}

}

void EnemyMush::UpdateState()
{
	m_animCount++;

	if (m_animCount > kAnimSpeed)// アニメーションスピード
	{
		m_animCount = 0;// はじめに戻す
		m_animFrame++;  // 次のコマへ
	}

	if (m_state == MushState::Normal)
	{
		if (m_animFrame >= kNormalFrame)// 通常 = 8
		{
			m_animFrame = 0;
		}
	}

	if (m_state == MushState::Damage)
	{
		if (m_animFrame >= kDamageFrame)// ヒット = 5
		{
			m_state = MushState::Normal;
			m_animFrame = 0;
		}
	}

	if (m_state == MushState::Death)
	{
		if (m_animFrame >= kDeathFrame)// 死 = 15
		{
			PlaySoundMem(m_effectSe, DX_PLAYTYPE_BACK);
			m_state = MushState::DeathEffect;
			m_animFrame = 0;
		}
	}
	if (m_state == MushState::DeathEffect)
	{
		if (m_animFrame >= kEffectFrame)// 死エフェクト = 12
		{
			Kill();
			m_animFrame = 0;
		}
	}
}

void EnemyMush::Draw(const Camera& camera)
{
	// キノコが死んでいたら何もしない
	if (!m_isAlive)return;

	Vec2 cam = camera.GetPos();

	// アニメーションのフレーム数から表示したいコマ番号
	int animNo = m_animFrame;
	// アニメーションの進行に合わせてグラフィックを切り取る
	int srcX = kGraphWidth * animNo;
	int srcY = 0;

	int w = kGraphWidth * kGraphicsSize;
	int h = kGraphHeight * kGraphicsSize;


	if (m_state == MushState::Normal)
	{
		DrawRectRotaGraph(static_cast<int>(m_pos.x - cam.x),
			static_cast<int>(m_pos.y - cam.y),//-35は地面への位置調整
			srcX, srcY,
			kGraphWidth, kGraphHeight, kGraphicsSize, kGraphicsAngle,
			m_handle, true, !m_isRight);
	}
	
	if (m_state == MushState::Damage)
	{
		DrawRectRotaGraph(static_cast<int>(m_pos.x - cam.x),
			static_cast<int>(m_pos.y - cam.y),
			srcX, srcY,
			kGraphWidth, kGraphHeight, kGraphicsSize, kGraphicsAngle,
			m_hitHandle, true, !m_isRight);
	}

	if (m_state == MushState::Death)
	{
		DrawRectRotaGraph(static_cast<int>(m_pos.x - cam.x),
			static_cast<int>(m_pos.y - cam.y),
			srcX, srcY,
			kGraphWidth, kGraphHeight, kGraphicsSize, kGraphicsAngle,
			m_deathHandle, true, !m_isRight);
	}

	if (m_state == MushState::DeathEffect)
	{
		int effectSrcX = kEffectWidth * m_animFrame;
		int effectSrcY = 0;
		DrawRectRotaGraph(static_cast<int>(m_pos.x - cam.x),
			static_cast<int>(m_pos.y - cam.y),
			effectSrcX, effectSrcY,
			kEffectWidth, kEffectHeight, kEffectSize, kGraphicsAngle,
			m_effectHandle, true, !m_isRight);

	}
	
#ifdef _DEBUG
	// 当たり判定（キノコ）の描画
	DrawBox(static_cast<int>(m_pos.x - cam.x - w / 5),
		static_cast<int>(m_pos.y - cam.y - 5 - h / 10),
		static_cast<int>(m_pos.x - cam.x + w / 5),
		static_cast<int>(m_pos.y - cam.y - 5 + h / 3),
		GetColor(255, 0, 0), false);
#endif // DEBUG
}
// 攻撃判定
void EnemyMush::Damage()
{
	
	if (m_damageCoolTime > 0)
	{
		return;
	}
	PlaySoundMem(m_hitSe, DX_PLAYTYPE_BACK);
	m_state = MushState::Damage;
	m_animFrame = 0;
	m_animCount = 0;

	m_hp--;

	// 止まる
	m_stopTimer = kStopTime;

	// 無敵時間
	m_damageCoolTime = kDamageCoolTime;


	if (m_hp <= 0)
	{
		PlaySoundMem(m_deathSe, DX_PLAYTYPE_BACK);
		m_state = MushState::Death;
		m_animFrame = 0;
		m_animCount = 0;
	}
}
// 当たり判定
Rect EnemyMush::EnemyMushHitBox() const
{

	if (m_state == MushState::Death||m_state == MushState::DeathEffect)
	{
		return Rect{ 0,0,0,0 };
	}
	float w = kGraphWidth * kGraphicsSize;
	float h = kGraphHeight * kGraphicsSize;

	Rect r;
	r.left = m_pos.x - w / 5;
	r.top = m_pos.y - 5 - h / 10;
	r.right = m_pos.x + w / 5;
	r.bottom = m_pos.y - 5 + h / 3;

	return r;
}

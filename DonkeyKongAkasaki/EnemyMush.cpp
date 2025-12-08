#include "EnemyMush.h"
#include "Character.h"
#include <DxLib.h>


namespace
{
	constexpr int kIdleAnimNum = 9;                  // プレイヤーのIdleアニメーション
	constexpr int kAnimWaitFrame = 1;                // ↑ 1コマ当たりのフレーム数
	constexpr int kGraphicsAngle = 0;                // グラフィックアングル
	constexpr int kGraphWidth = 64; // プレイヤーのグラフィックサイズ（幅）
	constexpr int kGraphHeight = 64;                // プレイヤーのグラフィックサイズ（高さ）
	constexpr int kSpeed = 3;                        // コウモリのスピード
	constexpr float kGraphicsSize = 5.0f;            // グラフィックサイズ

}

EnemyMush::EnemyMush():
	m_animFrame(0),
	m_animCount(0),
	m_normalAnim(0)
{
}

EnemyMush::~EnemyMush()
{
	DeleteGraph(m_handle);
}

void EnemyMush::Init()
{
	m_handle = LoadGraph("data/bat.png");
	m_pos = { 500.0f,600.0f };
}

void EnemyMush::Update()
{
	Character::Update();
	m_moveTimer++;
	if (m_moveTimer >= 180)
	{
		m_moveLeft = !m_moveLeft;
		m_moveTimer = 0;
	}
	if (m_moveLeft)
	{
		m_pos.x -= 1;
	}
	else
	{
		m_pos.x += 1;
	}

}

void EnemyMush::Damage()
{
	m_hp--;

	if (m_hp <= 0)
	{
		Kill();
	}
}

void EnemyMush::Draw(const Camera& camera)
{
	// コウモリが死んでいたら何もしない
	if (!m_isAlive)return;

	Vec2 cam = camera.GetPos();

	// アニメーションのフレーム数から表示したいコマ番号
	int animNo = m_animFrame;
	// アニメーションの進行に合わせてグラフィックを切り取る
	int srcX = kGraphWidth * animNo;
	int srcY = 0;

	int w = kGraphWidth * kGraphicsSize;
	int h = kGraphHeight * kGraphicsSize;


	DrawRectRotaGraph(static_cast<int>(m_pos.x - cam.x),
		static_cast<int>(m_pos.y - cam.y),//-35は地面への位置調整
		srcX, srcY,
		kGraphWidth, kGraphHeight, kGraphicsSize, kGraphicsAngle,
		m_handle, true);
#ifdef _DEBUG
	// 当たり判定（コウモリ）の描画
	DrawBox(static_cast<int>(m_pos.x - cam.x - w / 3),
		static_cast<int>(m_pos.y - cam.y - 35 - h / 10),
		static_cast<int>(m_pos.x - cam.x + w / 3),
		static_cast<int>(m_pos.y - cam.y - 35 + h / 3),
		GetColor(255, 0, 0), false);
#endif // DEBUG
}

Rect EnemyMush::EnemyMushHitBox() const
{
	float w = kGraphWidth * kGraphicsSize;
	float h = kGraphHeight * kGraphicsSize;

	Rect r;
	r.left = m_pos.x - w / 3;
	r.top = m_pos.y - 35 - h / 10;
	r.right = m_pos.x + w / 3;
	r.bottom = m_pos.y - 35 + h / 3;

	return r;
}

#include "EnemyBat.h"
#include "Character.h"
#include <DxLib.h>

// 普通に動くけど、描画がされない...SceneMainに入ってない&namespaceあたりがプレイヤーから持ってきただけ
// SceneMainにも反映されてない

namespace
{
	constexpr int kIdleAnimNum = 9;                  // プレイヤーのIdleアニメーション
	constexpr int kAnimWaitFrame = 1;                // ↑ 1コマ当たりのフレーム数
	constexpr int kGraphicsAngle = 0;                // グラフィックアングル
	constexpr int kGraphWidth = 64; // プレイヤーのグラフィックサイズ（幅）
	constexpr int kGraphHeight = 64;                // プレイヤーのグラフィックサイズ（高さ）
	constexpr float kGraphicsSize = 4.0f;            // グラフィックサイズ
}

EnemyBat::EnemyBat():
	m_animFrame(0),
	m_animCount(0),
	m_normalAnim(0)
{
}

EnemyBat::~EnemyBat()
{
	DeleteGraph(m_handle);
}

void EnemyBat::Init()
{
	m_handle = LoadGraph("data/bat.png");
}

void EnemyBat::Update()
{
	Character::Update();
}

void EnemyBat::Draw(const Camera& camera)
{
	Vec2 cam = camera.GetPos();

	// アニメーションのフレーム数から表示したいコマ番号
	int animNo = m_animFrame;
	// アニメーションの進行に合わせてグラフィックを切り取る
	int srcX = kGraphWidth * animNo;
	int srcY = 0;


	DrawRectRotaGraph(static_cast<int>(m_pos.x-cam.x),
		static_cast<int>(m_pos.y-cam.y),//-35は地面への位置調整
		srcX, srcY,
		kGraphWidth, kGraphHeight, kGraphicsSize, kGraphicsAngle,
		m_handle, true);
#ifdef _DEBUG
	// 当たり判定（自分）の描画
	DrawBox(static_cast<int>(m_pos.x),
		static_cast<int>(m_pos.y),
		static_cast<int>(m_pos.x + 32),
		static_cast<int>(m_pos.y),
		GetColor(0, 255, 255), false);
#endif // DEBUG
}

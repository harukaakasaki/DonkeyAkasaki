#include "Character.h"
#include <DxLib.h>
#include "Player.h"
#include "Camera.h"
#include "Vec2.h"


namespace
{
	constexpr float kGravity = 1.0f;// 重力
	constexpr float kGround = 640.0f;// 地面
}

/// <summary>
/// コンストラクタ
/// </summary>
Character::Character() :
	m_handle(-1),
	m_attackHandle(-1),
	m_moveHandle(-1),
	m_pos(),
	m_move(),
	m_isGround(false),
	m_isRight(true)
{
}

/// <summary>
/// デストラクタ
/// </summary>
Character::~Character()
{
}

/// <summary>
/// 初期化
/// </summary>
void Character::Init()
{

}

/// <summary>
/// 更新
/// </summary>
void Character::Update()
{
	// 重力
	Gravity();

	Rect chipRect;// 当たったマップチップの矩形

}

/// <summary>
/// 重力
/// </summary>
void Character::Gravity()
{
	// 重力分、下に落ちる
	m_move.y += kGravity;

	if (m_pos.y >= kGround)
	{
		// 地面にいる時の処理
		m_pos.y = kGround;
		m_move.y = 0.0f;
		m_isGround = true;
	}
	else
	{
		// 地面にいないときの処理
		/*m_isGround = false;*/
	}
}




/// <summary>
/// 描画
/// </summary>
void Character::Draw(Camera& camera)
{
	Vec2 cameraPos= camera.GetPos();
}

// 矩形
Rect Character::GetRect() const
{
	constexpr float kWidth = 64.0f;
	constexpr float kHeight = 64.0f;

	return
	{
		m_pos.x,
		m_pos.y,
		m_pos.x + kWidth,
		m_pos.y + kHeight,
	};
}

// 地面のマップチップの当たり判定
void Character::ResolveCollision(const Rect& chipRect)
{
	if (m_move.y > 0.0f)
	{
		m_pos.y = chipRect.top - 64.0f;
		m_move.y = 0.0f;
		m_isGround = true;
	}
}


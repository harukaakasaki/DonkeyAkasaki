#include "Character.h"
#include <DxLib.h>


namespace
{
	constexpr float kGravity = 1.5f;
	constexpr float kGround = 900.0f;
}

/// <summary>
/// コンストラクタ
/// </summary>
Character::Character():
	m_handle(-1),
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
	Gravity();

	m_move.y += kGravity;
	m_pos.y += m_move.y;

	if (m_pos.y + m_move.y >= kGround)
	{
		// 地面にいる時の処理
		m_pos.y = kGround - 32;
		m_move.y = 0;
//		m_isGround = true;
	}
	else
	{
		// 地面にいないときの処理
//		m_isGround = false;
	}
}

void Character::Gravity()
{
	m_move.y += kGravity;
}

/// <summary>
/// 描画
/// </summary>
void Character::Draw()
{
	DrawGraphF(0, 50, m_handle, true);
}

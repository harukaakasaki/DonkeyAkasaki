#include "Player.h"
#include "DxLib.h"
#include "Pad.h"

/// <summary>
/// コンストラクタ
/// </summary>
Player::Player():
	x(0),
	y(0)
{
	m_handle = LoadGraph("data/player.png");
}

/// <summary>
/// デストラクタ
/// </summary>
Player::~Player()
{
	DeleteGraph(m_handle);
}

/// <summary>
/// 初期化
/// </summary>
void Player::Init()
{
}

/// <summary>
/// 更新
/// </summary>
void Player::Update()
{
}

/// <summary>
/// 描画
/// </summary>
void Player::Draw()
{
	DrawGraph(0, 0, m_handle, true);
}
/// <summary>
/// プレイヤーを動かす
/// </summary>
void Player::Move()
{
}

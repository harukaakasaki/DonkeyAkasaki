#include "Player.h"
#include "DxLib.h"
#include "Pad.h"
#include"Character.h"
#include"SceneMain.h"

// 単純に四角(プレイヤーを動かす)


namespace
{
	constexpr float kSpeed = 10.0f;   //スピード
	constexpr float kGravity = 1.2f;  //重力
	constexpr float kGround = 640.0f; //地面の位置


	//constexpr int kPlayerAnimNum = 8; // プレイヤーのアニメーション
	//constexpr int kAnimWaitFrame = 4; // ↑ 1コマ当たりのフレーム数
	//constexpr int kGraphWidth    = 32;// プレイヤーのグラフィックサイズ（幅）
	//constexpr int kGraphHeight   = 32;// プレイヤーのグラフィックサイズ（高さ）
}

/// <summary>
/// コンストラクタ
/// </summary>
Player::Player():
	m_x(0),
	m_y(0),
	m_vecX(0),
	m_vecY(0),
	m_isGround(false)
//	m_animFrame(0)
{
	/*m_handle = LoadGraph("data/player.png");*/
}

/// <summary>
/// デストラクタ
/// </summary>
Player::~Player()
{
	/*DeleteGraph(m_handle);*/
}

/// <summary>
/// 初期化
/// </summary>
void Player::Init()
{
//	m_animFrame = 0;

	m_x = 500;
	m_y = 100;
}

/// <summary>
/// 更新
/// </summary>
void Player::Update()
{
	// アニメーション
	/*m_animFrame++;
	if (m_animFrame >= kPlayerAnimNum * kAnimWaitFrame)
	{
		m_animFrame = 0;
	}
	Character::Update();*/

	// 重力を付ける
	Gravity();

}

/// <summary>
/// プレイヤーを動かす
/// </summary>
void Player::Move()
{
}

void Player::Gravity()
{
	m_vecY += kGravity;
	m_y += m_vecY;

	if (m_y + m_vecY >= kGround)
	{
		// 地面にいる時の処理
		m_y = kGround;
		m_vecY = 0;
		m_isGround = true;
	}
	else
	{
		// 地面にいないときの処理
		m_isGround = false;
	}
}


/// <summary>
/// 描画
/// </summary>
void Player::Draw()
{
	// プレイヤー（四角）を描画
	DrawBox(static_cast<int>(m_x), static_cast<int>(m_y),
		    static_cast<int>(m_x+32), static_cast<int>(m_y+32),
		    GetColor(0, 255, 255), false);

	//// アニメーションのフレーム数から表示したいコマ番号
	//int animNo = m_animFrame / kAnimWaitFrame;
	//// アニメーションの進行に合わせてグラフィックを切り取る
	//int srcX = kGraphWidth * animNo;
	//int srcY = 0;
	//// アニメーションの描画
	//DrawGraph(0, 0, m_handle, true);

	/*DrawRectGraph(static_cast<int>(m_pos.x) - kGraphWidth / 2,
		static_cast<int>(m_pos.y) - kGraphHeight / 2,
		srcX, srcY, kGraphWidth, kGraphHeight,
		m_handle, true, m_isRight);*/
}

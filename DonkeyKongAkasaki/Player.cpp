#include "Player.h"
#include <DxLib.h>
#include "Pad.h"
#include"Character.h"
#include"SceneMain.h"
#include "Vec2.h"



namespace
{
	constexpr int kIdleAnimNum    = 7;                  // プレイヤーのIdleアニメーション
	constexpr int kAnimWaitFrame  = 4;                  // ↑ 1コマ当たりのフレーム数
	constexpr int kGraphicsAngle  = 0;                  // グラフィックアングル
	constexpr int kGraphWidth     = 1008 / kIdleAnimNum;// プレイヤーのグラフィックサイズ（幅）
	constexpr int kGraphHeight    = 144;                // プレイヤーのグラフィックサイズ（高さ）
	constexpr float kGraphicsSize = 4.0f;               // グラフィックサイズ
	constexpr float kSpeed        = 5.0f;               // スピード
	constexpr float kJumpPower    = 10.0f;               // ジャンプ力
//	constexpr float kGround = 640.0f;                   //地面の位置
}

// コンストラクタ
Player::Player() :
	m_x(0),
	m_y(0),
	m_vecX(0),
	m_vecY(0),
	m_animFrame(0)
{
	m_handle = LoadGraph("data/player_img.png");
}

// デストラクタ
Player::~Player()
{
	DeleteGraph(m_handle);
}

// 初期化
void Player::Init()
{
	m_animFrame = 0;
}

// 更新
void Player::Update()
{
	Character::Update();
	
	// アニメーション
	Animation();

	// ジャンプする
	Jump();
	// 移動する
	Move();
	m_pos += m_move;
	

}

// 移動
void Player::Move()
{
	if (Pad::IsPress(PAD_INPUT_LEFT))// 左入力で左方向に移動
	{
		m_move.x = -kSpeed;
//		m_pos.y -= 20;// スキップしてるみたいな動きになる
		m_isRight = false;
	}
	else if (Pad::IsPress(PAD_INPUT_RIGHT))// 右入力で右方向に移動
	{
		m_move.x = kSpeed;
//		m_pos.y -= 20;// スキップしてるみたいな動きになる
		m_isRight = true;
	}
	else// 何も入力がなかったら動かない
	{
		m_move.x = 0.0f;
	}
}
// アニメーション
void Player::Animation()
{
	m_animFrame++;
	if (m_animFrame >= kIdleAnimNum * kAnimWaitFrame)
	{
		m_animFrame = 0;
	}
}
// ジャンプ
void Player::Jump()
{
	if (Pad::IsPress(PAD_INPUT_2))
	{
		m_move.y = -kJumpPower;
	}
}

// 描画
void Player::Draw()
{
	// プレイヤーを描画
	// アニメーションのフレーム数から表示したいコマ番号
	int animNo = m_animFrame / kAnimWaitFrame;
	// アニメーションの進行に合わせてグラフィックを切り取る
	int srcX = kGraphWidth * animNo;
	int srcY = 0;
	// アニメーションの描画
	DrawRectRotaGraph(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y - 35),//-35は地面への位置調整
		srcX, srcY, kGraphWidth, kGraphHeight, kGraphicsSize, kGraphicsAngle,
		m_handle, true, !m_isRight);


	// デバッグ時にだけ動く処理
#ifdef _DEBUG
	// 当たり判定（四角）の描画
	DrawBox(static_cast<int>(m_pos.x - 40), static_cast<int>(m_pos.y - 90),
		static_cast<int>(m_pos.x + 32), static_cast<int>(m_pos.y),
		GetColor(0, 255, 255), false);
#endif // DEBUG

}



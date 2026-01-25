#include "Player.h"
#include <DxLib.h>
#include "Pad.h"
#include "Character.h"
#include "SceneMain.h"
#include "Vec2.h"
#include "Camera.h"
#include "Game.h"

namespace
{
	constexpr int	kIdleAnimNum	= 7;				    // プレイヤーのIdleアニメーション
	constexpr int	kAnimWaitFrame	= 1;					// ↑ 1コマ当たりのフレーム数
	constexpr int	kGraphicsAngle	= 0;					// グラフィックアングル
	constexpr int	kGraphWidth		= 1008 / kIdleAnimNum;	// プレイヤーのグラフィックサイズ（幅）
	constexpr int	kGraphHeight	= 144;					// プレイヤーのグラフィックサイズ（高さ）
	constexpr float	kTrapGround		= 930.0f;				// トラップ
	constexpr float kGraphicsSize	= 4.8f;					// グラフィックサイズ
	constexpr float kHpSize			= 0.09f;				// HPグラフィックサイズ
	constexpr float kSpeed			= 10.0f;					// スピード
	constexpr float kJumpPower		= 20.0f;				// ジャンプ力
	constexpr float kAnimSpeed		= 2.0f;					// アニメーションスピード
	constexpr float knockBackX		= 12.0f;				// ノックバックX
	constexpr float knockBackY		= 15.0f;				// ノックバックY
}

// コンストラクタ
Player::Player():
	m_vecX(0),
	m_vecY(0),
	m_animFrame(0),
	m_normalAnim(),
	m_attackAnim(),
	m_moveAnim(),
	m_deathAnim(),
	m_hitAnim(),
	m_jumpAnim()
{
	m_handle = LoadGraph("data/player_img.png");     // 通常時の画像、Level別で色が変わる
	m_attackHandle = LoadGraph("data/player_attack_1.png");// アタック時の画像
	m_moveHandle = LoadGraph("data/player_move.png");// 移動時の画像
	m_deathHandle = LoadGraph("data/player_death.png"); // プレイヤー死画像
	m_hitHandle = LoadGraph("data/player_hit3.png"); // プレイヤーヒット画像
	m_hpHandle = LoadGraph("data/hp.png"); // プレイヤーHP画像
	
}

// デストラクタ
Player::~Player()
{
	DeleteGraph(m_handle);
	DeleteGraph(m_attackHandle);
	DeleteGraph(m_moveHandle);
	DeleteGraph(m_deathHandle);
	DeleteGraph(m_hitHandle);
	DeleteGraph(m_hpHandle);
	DeleteSoundMem(m_jumpSe);
	DeleteSoundMem(m_attackSe);
	DeleteSoundMem(m_hitSe);
	DeleteSoundMem(m_deathSe);
}

// 初期化
void Player::Init()
{
	m_jumpSe = LoadSoundMem("bgm/player_jump_se2.mp3");
	m_attackSe = LoadSoundMem("bgm/player_attack_se2.mp3");
	m_hitSe = LoadSoundMem("bgm/player_hit_se.mp3");
	m_deathSe = LoadSoundMem("bgm/player_death_se2.mp3");

	m_state = PlayerState::Normal;
	m_hpMax = 3;
	m_hp = m_hpMax;

	m_animFrame = 0;
	
	m_pos.x = Game::kScreenWidth * 0.5f;
	m_pos.y = 890.0f;
	m_spawnPos.x = m_pos.x;
	m_spawnPos.y = m_pos.y;
	m_damageCoolTime = 0;
	
	m_spawnTimer = 0;
}

// 更新
void Player::Update()
{
	// 今の状態に応じてアニメーションを更新する
	UpdateState();

	m_frame++;

	if (m_state == PlayerState::Respawn)
	{
		return;
	}

	// トラップに当たったら死！
	if (m_pos.y >= kTrapGround)
	{
		// 既にDeathなら何もしない
		if (m_state != PlayerState::Death)
		{
			ChangeVolumeSoundMem(200, m_deathSe);
			PlaySoundMem(m_deathSe, DX_PLAYTYPE_BACK);

			m_state = PlayerState::Death;
			m_animFrame = 0;
			m_animCount = 0;
			m_spawnTimer = 0;
		}

	}
	if (m_state == PlayerState::Death)
	{
		m_isDamage = true;
		m_spawnTimer++;
		if (m_spawnTimer >= 120)
		{
			m_state = PlayerState::Respawn;
			Respawn();
		}

		return;
	}

		Character::Update();

		if (m_damageCoolTime > 0)
		{
			m_damageCoolTime--;
		}

		// 入力された状態に変わる
		HandleInput();

		// ジャンプする
		Jump();
		// 移動する
		Move();
		m_pos += m_move;

	}
// 移動
void Player::Move()
{
	if (m_state == PlayerState::Damage ||
		m_state == PlayerState::Death ||
		m_state == PlayerState::Respawn
		)
	{
		return;
	}

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
// ジャンプ
void Player::Jump()
{
	// 地面にいない場合、複数飛ぶことはできない
	if (!m_isGround)
	{
		return;
	}

	// XキーorPADのBボタンを押す
	if (Pad::IsTrigger(PAD_INPUT_1))
	{
		m_move.y = -kJumpPower;
		m_isGround = false;

		ChangeVolumeSoundMem(150, m_jumpSe);
		PlaySoundMem(m_jumpSe, DX_PLAYTYPE_BACK);
	}
}



void Player::HandleInput()
{
	
	
	// AttackStateに変更
	if (m_state == PlayerState::Attack)
	{
		return;
	}
	 
	if (Pad::IsTrigger(PAD_INPUT_3))
	{
		// 攻撃に変更
		m_state = PlayerState::Attack;
		// 攻撃モーションをはじめからにする
		m_animFrame = 0;
		// アニメーションカウンターをリセット
		m_animCount = 0;
		ChangeVolumeSoundMem(200, m_attackSe);
		PlaySoundMem(m_attackSe, DX_PLAYTYPE_BACK);
	}
}

// Playerの状態を更新
void Player::UpdateState()
{
	m_animCount++;

	if (m_animCount > 2)// アニメーションスピード
	{
		m_animCount = 0;// はじめに戻す
		
		if (m_state == PlayerState::Respawn)
		{
			 m_animFrame--;
		}
		else
		{
			m_animFrame++;// 次のコマへ
		}
	}


	if (m_state == PlayerState::Normal)
	{
		if (m_animFrame >= 7)// 通常 = 7
		{
			m_animFrame = 0;

		}
	}
	if (m_state == PlayerState::Damage)
	{
		if (m_animFrame >= 3)// ヒット = 3
		{
			m_state = PlayerState::Normal;
			m_animFrame = 0;

		}
	}
	
	//移動モーションの状態

	else if (m_state == PlayerState::Move)
	{
		if (m_animFrame >= 8)// 移動 = 8
		{
		// 移動アニメーションが最後まで行ったら、
		// 自動でNormal状態に戻す
			m_state = PlayerState::Normal;
			m_animFrame = 0;
		}
	}
	else if (m_state == PlayerState::Attack)
	{
		// 攻撃アニメーションが最後まで行ったら、
		// 自動でNormal状態に戻す
		if (m_animFrame >= 10)// 攻撃 = 10
		{
			m_state = PlayerState::Normal;
			m_animFrame = 0;
		}
	}
	if (m_state == PlayerState::Respawn)
	{
		if (m_animFrame <= 0)// ヒット = 3
		{
			m_state = PlayerState::Normal;
			m_animFrame = 0;

		}
	}
}

// HP描画
void Player::DrawHP()
{
	if (m_state == PlayerState::Death)
	{
		m_hp = 0;
	}
	// ハートの位置
	const int startX = 100;
	const int startY = 100;
	const int interval = 120; // hpの間隔
	const double scale = kHpSize;// hpの大きさ

	for (int i = 0; i < m_hp; i++)
	{
		DrawRotaGraph(
			startX + i * interval,
			startY,
			scale,
			0.0,
			m_hpHandle,
			true);
	}
}

bool Player::IsAttackHitActive() const
{
	// 攻撃アニメーション(10アニメーション中3～5の間だけ攻撃判定)
	return (m_state == PlayerState::Attack && m_animFrame >= 3 && m_animFrame <= 5);
}

// 攻撃当たり判定
Rect Player::AttackHitBox() const
{
	Rect r;

	int attackW = 160;
	int attackH = 90;

	if (m_isRight)
	{
		r.left = m_pos.x;
		r.right = m_pos.x + attackW;
	}
	else
	{
		r.left = m_pos.x - attackW;
		r.right = m_pos.x;
	}

	r.top = m_pos.y - attackW;
	r.bottom = m_pos.y;

	return r;
}

// Player自身の当たり判定
Rect Player::PlayerHitBox() const
{
	Rect r;

	r.left = m_pos.x - 40;
	r.right = m_pos.x + 32;
	r.top = m_pos.y - 90;
	r.bottom = m_pos.y;

	return r;
}

void Player::Damage(float hitDir)
{
#ifdef _DEBUG
	printfDx("Player::Damege called\n");
#endif
	if (m_damageCoolTime > 0)
	{
		return;
	}

	m_isDamage = true;

	m_hp--;
	m_damageCoolTime = 30;



	m_state = PlayerState::Damage;

	// ヒット時のノックバック
	m_move.x = knockBackX * hitDir;
	m_move.y = -knockBackY;


	m_animFrame = 0;
	m_animCount = 0;

	m_isGround = false;


	if (m_hp <= 0)
	{
		if (m_state != PlayerState::Death)
		{
			ChangeVolumeSoundMem(200, m_deathSe);
			PlaySoundMem(m_deathSe, DX_PLAYTYPE_BACK);
			m_state = PlayerState::Death;
			m_animFrame = 0;
			m_animCount = 0;
			m_spawnTimer = 0;
		}
		return;
	}
	ChangeVolumeSoundMem(200, m_hitSe);
	PlaySoundMem(m_hitSe, DX_PLAYTYPE_BACK);
}


void Player::Respawn()
{
	m_pos = m_spawnPos;
	m_hp = 3;
	m_state = PlayerState::Respawn;

	m_move = Vec2(0, 0);
	m_isGround = false;

	m_animFrame = 18;
	m_animCount = 0;
	m_damageCoolTime = 0;
	m_spawnTimer = 0;

	m_isRespawn = true;
}

// 描画
void Player::Draw(Camera& camera)
{
	Vec2 cameraPos;

	cameraPos = camera.GetPos();


	// プレイヤーを描画
	// アニメーションのフレーム数から表示したいコマ番号
	int animNo = m_animFrame / kAnimWaitFrame;
	// アニメーションの進行に合わせてグラフィックを切り取る
	int srcX = kGraphWidth * animNo;
	int srcY = 0;
	if (m_state == PlayerState::Respawn)
	{
		DrawRectRotaGraph(static_cast<int>(m_pos.x) - cameraPos.x,
			static_cast<int>(m_pos.y - 35) - cameraPos.y,//-35は地面への位置調整
			srcX, srcY,
			kGraphWidth, kGraphHeight, kGraphicsSize, kGraphicsAngle,
			m_deathHandle, true, !m_isRight);
	}
	
	// 死アニメーション
	if (m_state == PlayerState::Death)
	{
		DrawRectRotaGraph(static_cast<int>(m_pos.x) - cameraPos.x,
			static_cast<int>(m_pos.y - 35) - cameraPos.y,//-35は地面への位置調整
			srcX, srcY,
			kGraphWidth, kGraphHeight, kGraphicsSize, kGraphicsAngle,
			m_deathHandle, true, !m_isRight);
	}
	// ダメージアニメーション
	if (m_state == PlayerState::Damage)
	{
		DrawRectRotaGraph(static_cast<int>(m_pos.x) - cameraPos.x,
			static_cast<int>(m_pos.y - 35) - cameraPos.y,//-35は地面への位置調整
			srcX, srcY,
			kGraphWidth, kGraphHeight, kGraphicsSize, kGraphicsAngle,
			m_hitHandle, true, !m_isRight);
		//if (m_frame / 30 % 2 == 0)
		//{
		//	DrawRectRotaGraph(static_cast<int>(m_pos.x) - cameraPos.x,
		//		static_cast<int>(m_pos.y - 35) - cameraPos.y,//-35は地面への位置調整
		//		srcX, srcY,
		//		kGraphWidth, kGraphHeight, kGraphicsSize, kGraphicsAngle,
		//		m_hitHandle, true, !m_isRight);
		//}

		//else
		//{
		//	SetDrawBright(255, 255, 255);
		//	DrawRectRotaGraph(static_cast<int>(m_pos.x) - cameraPos.x,
		//		static_cast<int>(m_pos.y - 35) - cameraPos.y,//-35は地面への位置調整
		//		srcX, srcY,
		//		kGraphWidth, kGraphHeight, kGraphicsSize, kGraphicsAngle,
		//		m_hitHandle, true, !m_isRight);
		//	SetDrawBright(0, 0, 0);
		//}
		
	}
	
	// 通常アニメーションの描画
	if (m_state == PlayerState::Normal)
	{
		DrawRectRotaGraph(static_cast<int>(m_pos.x)-cameraPos.x,
			static_cast<int>(m_pos.y - 35) - cameraPos.y,//-35は地面への位置調整
			srcX, srcY,
			kGraphWidth, kGraphHeight, kGraphicsSize, kGraphicsAngle,
			m_handle, true, !m_isRight);
		// デバッグの時のみ行う
#ifdef _DEBUG
		// 当たり判定（自分）の描画
		DrawBox(static_cast<int>(m_pos.x - 40) - cameraPos.x,
			static_cast<int>(m_pos.y - 90) - cameraPos.y,
			static_cast<int>(m_pos.x + 32) - cameraPos.x,
			static_cast<int>(m_pos.y) - cameraPos.y,
			GetColor(0, 255, 255), false);
#endif // DEBUG
	}

	// 移動アニメーション
	if (m_state == PlayerState::Move)
	{
		DrawRectRotaGraph(static_cast<int>(m_pos.x) - cameraPos.x,
			static_cast<int>(m_pos.y - 35) - cameraPos.y,//-35は地面への位置調整
			srcX, srcY,
			kGraphWidth, kGraphHeight, kGraphicsSize, kGraphicsAngle,
			m_moveHandle, true, !m_isRight);
	}
	// 左右上下
	int left, right, top, bottom;

	// 攻撃判定の大きさ
	int attackW = 160;
	int attackH = 90;

	// 攻撃モーションの描画
	if (m_state == PlayerState::Attack)
	{
		DrawRectRotaGraph(static_cast<int>(m_pos.x) - cameraPos.x,
			static_cast<int>(m_pos.y - 35) - cameraPos.y,//-35は地面への位置調整
			srcX, srcY, 
			kGraphWidth, kGraphHeight, kGraphicsSize, kGraphicsAngle,
			m_attackHandle, true, !m_isRight);
#ifdef _DEBUG
		// 右を向いているとき、右にだけ攻撃判定
		if (m_isRight)
		{
			left  = static_cast<int>(m_pos.x);
			right = static_cast<int>(m_pos.x + attackW);
		}
		// 左を向いているとき、左にだけ攻撃判定
		else
		{
			left = static_cast<int>(m_pos.x - attackW);
			right = static_cast<int>(m_pos.x);
		}
		top = static_cast<int>(m_pos.y - attackH);
		bottom = static_cast<int>(m_pos.y);

		// 当たり判定（自分）の描画
		DrawBox(static_cast<int>(m_pos.x - 40) - cameraPos.x,
			static_cast<int>(m_pos.y - 90) - cameraPos.y,
			static_cast<int>(m_pos.x + 32) - cameraPos.x,
			static_cast<int>(m_pos.y) - cameraPos.y,
			GetColor(0, 255, 255), false);

		// 当たり判定（攻撃）の描画
		DrawBox(left - cameraPos.x, top - cameraPos.y, 
			right - cameraPos.x, bottom - cameraPos.y, 
			GetColor(255, 0, 0), false);
		
#endif // _DEBUG
		
	}
}
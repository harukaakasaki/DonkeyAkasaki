#pragma once
#include "Character.h"

class Player : public Character
{
	/// <summary>
	/// プレイヤーの状態
	/// </summary>
	enum class PlayerState
	{
		Normal,// 通常
		Move,  // 移動
		Jump,  // ジャンプ
		Attack,// 攻撃
		Death,  // 死s
		Damage, // ダメージ
		Respawn // 復活
	};
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Player();
	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~Player()override;

	/// <summary>
	/// 初期化
	/// </summary>
	virtual void Init()override;
	/// <summary>
	/// 更新
	/// </summary>
	virtual void Update()override;
	/// <summary>
	/// 描画
	/// </summary>
	virtual void Draw(Camera&camera)override;
	/// <summary>
	/// ダメージ
	/// </summary>
	void Damage(float hitDir);
	/// <summary>
	/// リスポーン
	/// </summary>
	void Respawn();

	/// <summary>
	/// 攻撃判定
	/// </summary>
	/// <returns></returns>
	bool IsAttack()const { return m_state == PlayerState::Attack; }

	/// <summary>
	/// 攻撃当たり判定
	/// </summary>
	/// <returns></returns>
	Rect AttackHitBox() const;

	/// <summary>
	/// 当たり判定
	/// </summary>
	/// <returns></returns>
	Rect PlayerHitBox() const;

	/// <summary>
	/// HP描画
	/// </summary>
	void DrawHP();
	/// <summary>
	/// 攻撃時間
	/// </summary>
	/// <returns></returns>
	bool IsAttackHitActive() const;
	bool IsDamage()const { return m_isDamage; }
	void ClearDamage() { m_isDamage = false; }

	bool IsJustRespawn()const { return m_isRespawn; }
	void ClearJustRespawn() { m_isRespawn = false; }

private:
	bool m_isDamage = false;
	bool m_isRespawn = false;

	// 力X,Y
	float m_vecX;
	float m_vecY;

	PlayerState m_state = PlayerState::Normal;// 通常状態

	Vec2 m_spawnPos; // リスポーン位置
	int m_spawnTimer; // リスポーン時間

	int m_hpHandle; // 体力画像

	/// <summary>
	/// 移動
	/// </summary>
	void Move();
	/// <summary>
	/// 重力
	/// </summary>
	void Gravity();
	/// <summary>
	/// ジャンプ
	/// </summary>
	void Jump();


	/// <summary>
	/// キー入力処理
	/// </summary>
	void HandleInput();
	/// <summary>
	/// アニメーションの更新
	/// </summary>
	void UpdateState();

	int m_frame = 0;

	// アニメーションのフレーム数
	int m_animFrame = 0;
	// コマ送りのカウンタ
	int m_animCount = 0;

	int m_normalAnim[7]; // 通常コマ数
	int m_attackAnim[10];// 攻撃コマ数
	int m_moveAnim[8];   // 移動コマ数
	int m_jumpAnim[4];   // ジャンプコマ数
	int m_deathAnim[18];   // 死コマ数
	int m_hitAnim[3];   // ヒットコマ数

	int m_hp = 3; //HP
	int m_hpMax; //HP限界
	int m_damageCoolTime = 0; // 無敵

	// SE系
	int m_jumpSe;
	int m_attackSe;
	int m_deathSe;
	int m_hitSe;
	int m_runSe;
};


#pragma once
#include "Character.h"

/// <summary>
/// プレイヤーの状態
/// </summary>
enum class PlayerState
{
	Normal,// 通常
	Move,  // 移動
	Jump,  // ジャンプ
	Attack,// 攻撃
	Death  // 死
};
/// <summary>
/// プレイヤーのLevel状態
/// </summary>
enum class LevelState
{
	Level0,// 敵を0体倒した（Levelリセット）
	Level1,// 敵を1体倒した
	Level2,// 敵を2体倒した
	Level3 // 敵を3体倒した
};

class Player : public Character
{
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

	

private:
	// 力X,Y
	float m_vecX;
	float m_vecY;

	PlayerState m_state = PlayerState::Normal;// 通常状態
	LevelState m_level = LevelState::Level0;  // 最初の状態


	/// <summary>
	/// 移動
	/// </summary>
	void Move();
	/// <summary>
	/// 重力
	/// </summary>
	void Gravity();
	/// <summary>
	/// アニメーション
	/// </summary>
	//void Animation();
	/// <summary>
	/// ジャンプ
	/// </summary>
	void Jump();
	/// <summary>
	/// 攻撃
	/// </summary>
	/*void Attack();*/

	/// <summary>
	/// キー入力処理
	/// </summary>
	void HandleInput();
	/// <summary>
	/// アニメーションの更新
	/// </summary>
	void UpdateState();

	

	// アニメーションのフレーム数
	int m_animFrame = 0;
	// コマ送りのカウンタ
	int m_animCount = 0;

	int normalAnim[7]; // 通常コマ数
	int attackAnim[10];// 攻撃コマ数
	int moveAnim[8];   // 移動コマ数
	int jumpAnim[4];   // ジャンプコマ数

};


#pragma once
#include "Character.h"
class Player: public Character
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
	virtual void Draw()override;

private:
	// 座標X,Y
	float m_x;
	float m_y;
	// 力X,Y
	float m_vecX;
	float m_vecY;


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
	void Animation();
	/// <summary>
	/// ジャンプ
	/// </summary>
	void Jump();

	// アニメーションのフレーム数
	int m_animFrame;
};


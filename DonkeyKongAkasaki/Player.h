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


	// 移動
	void Move();
	// 重力
	void Gravity();

	// プレイヤーのアニメーション
//	int m_animFrame;
};


#pragma once
#include "Vec2.h"

class Rect;
class Camera;
class Character
{
public:
	Character();
	virtual ~Character();

	virtual void Init();
	virtual void Update();
	virtual void Draw(Camera& camera);

	/// <summary>
	/// プレイヤーの現在の位置を取得
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <returns></returns>
	const Vec2 GetPos()const { return m_pos; }

protected:
	// キャラクターの画像
	int m_handle;
	// キャラクターの移動画像
	int m_moveHandle;
	// キャラクターの攻撃画像
	int m_attackHandle;
	// 座標
	Vec2 m_pos;
	// 移動量
	Vec2 m_move;
	// 右を向いているのか
	bool m_isRight;
	// 地面についているのか
	bool m_isGround;
	// 重力
	void Gravity();
	// マップチップとの当たり判定
	void CheckHitMap(Rect& chipRect);

	

};


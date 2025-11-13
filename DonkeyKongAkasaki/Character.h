#pragma once
#include "Vec2.h"
class Character
{
public:
	Character();
	virtual ~Character();

	virtual void Init();
	virtual void Update();
	virtual void Draw();

protected:
	// キャラクターの画像
	int m_handle;
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

};


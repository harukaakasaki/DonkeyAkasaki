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

protected:
	// 座標
	Vec2 m_pos;

protected:
	// 右を向いているのか
	bool m_isRight;
};


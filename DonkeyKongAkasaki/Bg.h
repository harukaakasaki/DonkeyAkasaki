#pragma once
#include "Vec2.h"

class Player;

class Bg
{
public:
	Bg(Player* pPlayer);
	~Bg();

	void Init();
	void Update();
	void Draw();

	int GetScrollX();

	int GetScrollY();

private:
	void DrawBg();

private:
	int m_bg1Handle;// ”wŒi1‚Ì‰æ‘œ
	int m_bg2Handle;// ”wŒi2‚Ì‰æ‘œ
	int m_bg3Handle;// ”wŒi3‚Ì‰æ‘œ
	Vec2 m_pos;// ”wŒi‚ÌˆÊ’u

	Player* m_pPlayer;
};


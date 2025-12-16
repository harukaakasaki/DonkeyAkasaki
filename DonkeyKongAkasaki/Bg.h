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

	void DrawMapChip();

	int GetScrollX();

	int GetScrollY();

private:
	void DrawBg();

private:
	int m_bg1Handle;// ”wŒi1‚Ì‰æ‘œ
	int m_bg2Handle;// ”wŒi2‚Ì‰æ‘œ
	int m_bg3Handle;// ”wŒi3‚Ì‰æ‘œ
	int m_mapHandle;// ƒ}ƒbƒvƒ`ƒbƒv‰æ‘œ
	Vec2 m_pos;// ”wŒi‚ÌˆÊ’u

	Player* m_pPlayer;
};


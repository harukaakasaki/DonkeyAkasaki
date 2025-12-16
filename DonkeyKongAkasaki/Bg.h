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
	// 画像に含まれるマップチップの数
	int m_mapChipNumX;// X
	int m_mapChipNumY;// Y

private:
	int m_bg1Handle;// 背景1の画像
	int m_bg2Handle;// 背景2の画像
	int m_bg3Handle;// 背景3の画像
	int m_mapHandle;// マップチップ画像
	Vec2 m_pos;// 背景の位置

	Player* m_pPlayer;
};


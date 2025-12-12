#pragma once
#include "Vec2.h"

class Bg
{
public:
	Bg();
	~Bg();

	void Init();
	void Update();
	void Draw();

private:
	void DrawBg();

private:
	int m_bg1Handle;// ”wŒi1‚Ì‰æ‘œ
	int m_bg2Handle;// ”wŒi2‚Ì‰æ‘œ
	int m_bg3Handle;// ”wŒi3‚Ì‰æ‘œ
	Vec2 m_pos;// ”wŒi‚ÌˆÊ’u
};


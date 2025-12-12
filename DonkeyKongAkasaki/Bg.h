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
	int m_bgHandle;// ”wŒi‚Ì‰æ‘œ
	Vec2 m_pos;// ”wŒi‚ÌˆÊ’u
};


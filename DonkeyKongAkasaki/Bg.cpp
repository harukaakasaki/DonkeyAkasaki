#include "Bg.h"
#include <DxLib.h>

Bg::Bg():
	m_pos{0,0}
{
	m_bgHandle = LoadGraph("data/bg_1.png");
}

Bg::~Bg()
{
	DeleteGraph(m_bgHandle);
}

void Bg::Init()
{

}

void Bg::Update()
{

}

void Bg::Draw()
{
	DrawBg();
}

void Bg::DrawBg()
{
	DrawGraph(m_pos.x, m_pos.y, m_bgHandle, true);
}

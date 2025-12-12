#include "Bg.h"
#include <DxLib.h>

Bg::Bg():
	m_pos{0,0}
{
	m_bg1Handle = LoadGraph("data/bg_1.png");
	m_bg2Handle = LoadGraph("data/bg_2.png");
	m_bg3Handle = LoadGraph("data/bg_3.png");
}

Bg::~Bg()
{
	DeleteGraph(m_bg1Handle);
	DeleteGraph(m_bg2Handle);
	DeleteGraph(m_bg3Handle);
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
	DrawGraph(m_pos.x, m_pos.y, m_bg1Handle, true);
	DrawGraph(m_pos.x, m_pos.y, m_bg2Handle, true);
	DrawGraph(m_pos.x, m_pos.y, m_bg3Handle, true);
}

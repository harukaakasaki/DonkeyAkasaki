#include "Bg.h"
#include <DxLib.h>
#include "Player.h"

namespace
{
	constexpr float kMapWidth = 5000.0f;// マップ全体の幅
	constexpr float kMapHeight = 1080.0f;// マップ全体の高さ
	constexpr float kScreenWidth = 1920.0f;// スクリーンの幅
	constexpr float kScreenHeight = 1080.0f;// スクリーンの高さ
}

struct Size
{
	int width;
	int height;
};

Bg::Bg(Player* pPlayer):
	m_pos{0,0},
	m_pPlayer(pPlayer)
{
	// 背景のイラスト
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

int Bg::GetScrollX()
{
	int result = static_cast<int>(m_pPlayer->GetPos().x - kScreenWidth * 0.5);
	if (result < 0)
	{
		result = 0;
	}

	if (result > kMapWidth - kScreenWidth)
	{
		result = kMapWidth - kScreenWidth;
	}
	
	return result;

}

int Bg::GetScrollY()
{
	int result = static_cast<int>(m_pPlayer->GetPos().y - kScreenHeight * 0.5);
	if (result < 0)
	{
		result = 0;
	}

	if (result > kMapHeight - kScreenHeight)
	{
		result = kMapHeight - kScreenHeight;
	}

	return result;

}

void Bg::DrawBg()
{
	Size bgSize = { 0,0 };
	GetGraphSize(m_bg1Handle, &bgSize.width, &bgSize.height);

	int scrollBg = GetScrollX() % bgSize.width;

	if (scrollBg < 0)scrollBg += bgSize.width;// マイナス対策

	// 横スクローループ
	for (int i = -1; i <= 1; i++)
	{
		DrawGraph(i * bgSize.width - scrollBg, m_pos.y, m_bg1Handle, true);
		DrawGraph(i * bgSize.width - scrollBg, m_pos.y, m_bg2Handle, true);
		//DrawGraph(i * bgSize.width - scrollBg, m_pos.y, m_bg3Handle, true);
	}

	/*DrawGraph(-scrollBg, m_pos.y, m_bg1Handle, true);
	DrawGraph(-scrollBg, m_pos.y, m_bg2Handle, true);
	DrawGraph(-scrollBg, m_pos.y, m_bg3Handle, true);*/
}

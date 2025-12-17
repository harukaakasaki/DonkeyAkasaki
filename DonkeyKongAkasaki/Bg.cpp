#include "Bg.h"
#include <DxLib.h>
#include "Player.h"
#include "Game.h"

namespace
{
	constexpr int kChipSize = 32;// マップチップの大きさ
	// マップチップを置く数
	constexpr int kChipNumX = 21;
	constexpr int kChipNumY = 14;

	constexpr float kMapWidth = 8000.0f;// マップ全体の幅
	constexpr float kMapHeight = 1080.0f;// マップ全体の高さ
	constexpr float kScreenWidth = 1920.0f;// スクリーンの幅
	constexpr float kScreenHeight = 1080.0f;// スクリーンの高さ
	constexpr float kChipScale = 2.0f;// マップチップの大きさ

	constexpr int kChipData[kChipNumY][kChipNumX] =
	{
		{21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21},
		{21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21},
		{21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21},
		{21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21},
		{21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21},
		{21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21},
		{21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21},
		{21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21},
		{21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21},
		{21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21},
		{4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4},
		{21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21},
		{21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21},
		{21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21}
	};
}

struct Size
{
	int width;
	int height;
};

Bg::Bg(Player* pPlayer):
	m_pos{0,0},
	m_pPlayer(pPlayer),
	m_mapChipNumX(0),
	m_mapChipNumY(0)
{
	// 背景のイラスト
	m_bg1Handle = LoadGraph("data/bg_1.png");
	m_bg2Handle = LoadGraph("data/bg_2.png");
	m_bg3Handle = LoadGraph("data/bg_3.png");
	m_mapHandle = LoadGraph("data/mapChip.png");
	// 画像マップチップ数を数える
	int graphW = 0;
	int graphH = 0;
	GetGraphSize(m_mapHandle, &graphW, &graphH);

	m_mapChipNumX = graphW / kChipSize;
	m_mapChipNumY = graphH / kChipSize;
	
}

Bg::~Bg()
{
	DeleteGraph(m_bg1Handle);
	DeleteGraph(m_bg2Handle);
	DeleteGraph(m_bg3Handle);
	DeleteGraph(m_mapHandle);
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
	DrawMapChip();
}

void Bg::DrawMapChip()
{
	/*DrawGraph(0, 0, m_mapHandle, true);*/

	for (int y = 0; y < kChipNumY; y++)
	{
		for (int x = 0; x < kChipNumX; x++)
		{
			int posX = static_cast<int>(x * kChipSize * kChipScale - GetScrollX());
			int posY = static_cast<int>(y * kChipSize * kChipScale - GetScrollY());

			// 設置するチップ
			int chipNo = kChipData[y][x];

			// マップチップのグラフィック切り出し位置//反応していない
			int srcX = (chipNo % m_mapChipNumX) * kChipSize;
			int srcY = (chipNo / m_mapChipNumX) * kChipSize;
			// 描画
			DrawRectRotaGraph(static_cast<int>(posX + kChipSize * kChipScale * 0.5f),
				static_cast<int>(posY + kChipSize * kChipScale * 0.5f),
				srcX, srcY,
				kChipSize, kChipSize, kChipScale, 0.0f,
				m_mapHandle, true);


#ifdef _DEBUG

			DrawBoxAA(posX, posY, posX + kChipSize * kChipScale, posY + kChipSize * kChipScale, 0x00ff00, false);

#endif // _DEBUG

		}
	}
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

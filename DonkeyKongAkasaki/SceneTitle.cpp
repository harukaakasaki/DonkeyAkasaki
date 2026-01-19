#include "SceneTitle.h"
#include "Pad.h"
#include "SceneMain.h"
#include <DxLib.h>

namespace
{
	constexpr float kScreenWidth = 1600.0f;// スクリーンの幅
	constexpr float kScreenHeight = 900.0f;// スクリーンの高さ

}


SceneTitle::SceneTitle()
{
	m_titleHandle = LoadGraph("data/TitleImage.png");
}

void SceneTitle::Update()
{
	if (Pad::IsTrigger(PAD_INPUT_1))
	{
		m_isEnd = true;
	}
}

void SceneTitle::Draw()
{
	DrawString(400, 300, "TitleScene", GetColor(255, 255, 255));
	DrawGraph(0, 0,m_titleHandle, true);

}

// 次のシーンに遷移する
Scene* SceneTitle::GetNextScene()
{
	return new SceneMain();
}

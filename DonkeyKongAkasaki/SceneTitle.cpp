#include "SceneTitle.h"
#include "Pad.h"
#include "SceneMain.h"
#include <DxLib.h>



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
}

Scene* SceneTitle::GetNextScene()
{
	return new SceneMain();
}

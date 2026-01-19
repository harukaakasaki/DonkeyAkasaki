#include "SceneClear.h"
#include "SceneTitle.h"
#include "Pad.h"
#include <DxLib.h>


void SceneClear::Update()
{
	if (Pad::IsTrigger(PAD_INPUT_1))
	{
		m_isEnd = true;
	}
}

void SceneClear::Draw()
{
	DrawString(400, 300, "CLEAR!!", GetColor(0, 255, 255));
}

Scene* SceneClear::GetNextScene()
{
	return new SceneTitle();
}
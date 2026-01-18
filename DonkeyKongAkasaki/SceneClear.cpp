#include "SceneClear.h"
#include "SceneMain.h"
#include <DxLib.h>


void SceneClear::Update()
{
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		m_isEnd = true;
	}
}

void SceneClear::Draw()
{
	DrawString(400, 300, "CLEAR!!", GetColor(255, 255, 0));
}

Scene* SceneClear::GetNextScene()
{
	return new SceneMain();
}
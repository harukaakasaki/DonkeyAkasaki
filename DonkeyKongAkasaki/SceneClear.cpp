#include "SceneClear.h"
#include "SceneTitle.h"
#include "Pad.h"
#include <DxLib.h>


SceneClear::SceneClear()
{
	m_bgmHandle = LoadSoundMem("bgm/clear_bgm.mp3");
	ChangeVolumeSoundMem(180, m_bgmHandle);
	PlaySoundMem(m_bgmHandle, DX_PLAYTYPE_LOOP);
}

SceneClear::~SceneClear()
{
	StopSoundMem(m_bgmHandle);
	DeleteSoundMem(m_bgmHandle);
}

void SceneClear::Update()
{
	if (Pad::IsTrigger(PAD_INPUT_8))
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
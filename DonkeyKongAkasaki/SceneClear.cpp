#include "SceneClear.h"
#include "SceneTitle.h"
#include "Pad.h"
#include <DxLib.h>


SceneClear::SceneClear() :
	m_scrollX(0.0f)
{
	m_bgmHandle = LoadSoundMem("bgm/clear_bgm.mp3");
	m_bgHandle = LoadGraph("data/clear3.png");
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
	m_scrollX += 1.0f;

	int bgW, bgH;
	GetGraphSize(m_bgHandle, &bgW, &bgH);

	if(m_scrollX >= bgW)
	{
		m_scrollX -= bgW;
	}


	if (Pad::IsTrigger(PAD_INPUT_8))
	{
		m_isEnd = true;
	}
}

void SceneClear::Draw()
{
	int bgW, bgH;
	GetGraphSize(m_bgHandle, &bgW, &bgH);

	DrawGraph(-m_scrollX, 0, m_bgHandle, true);
	DrawGraph(-m_scrollX +bgW,0, m_bgHandle, true);

	DrawString(400, 300, "CLEAR!!", GetColor(0, 255, 255));
}

Scene* SceneClear::GetNextScene()
{
	return new SceneTitle();
}
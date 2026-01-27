#include "SceneClear.h"
#include "SceneTitle.h"
#include "Pad.h"
#include <DxLib.h>


namespace
{
	int kPlayerScale = 6;
}

SceneClear::SceneClear() :
	m_scrollX(0.0f),
	m_animCount(0),
	m_animFrame(0)
{
	m_bgmHandle = LoadSoundMem("bgm/clear_bgm.mp3");
	m_bgHandle = LoadGraph("data/clear3.png");
	m_clearHandle = LoadGraph("data/spring_has_come.png");
	m_endHandle = LoadGraph("data/endButton.png");
	m_playerRunHandle = LoadGraph("data/player_move.png");
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
	m_scrollX += 3.0f;

	int bgW, bgH;
	GetGraphSize(m_bgHandle, &bgW, &bgH);

	if(m_scrollX >= bgW)
	{
		m_scrollX -= bgW;
	}

	m_animCount++;
	if (m_animCount > 4)
	{
		m_animCount = 0;
		m_animFrame++;
		if (m_animFrame >= 8)
		{
			m_animFrame = 0;
		}
	}


	if (Pad::IsTrigger(PAD_INPUT_8))
	{
		m_isEnd = true;
	}
	if (Pad::IsTrigger(PAD_INPUT_2))
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

	const int kFrameW = 1008/7;
	const int kFrameH = 144;

	int srcX = m_animFrame * kFrameW;
	int srcY = 0;

	DrawRectRotaGraph(
		550, 900,
		srcX, srcY,
		kFrameW, kFrameH,
		kPlayerScale,
		0.0f,
		m_playerRunHandle,
		true
	);
	DrawGraph(0, 0, m_clearHandle, true);
	DrawGraph(0, 0, m_endHandle, true);
}

Scene* SceneClear::GetNextScene()
{
	return new SceneTitle();
}
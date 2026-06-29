#include "SceneClear.h"
#include "SceneTitle.h"
#include "../Systems/Pad.h"
#include <DxLib.h>
#include <cmath>


namespace
{
	constexpr int kPlayerScale   = 6;   // プレイヤースケール
	constexpr int kPlayerX       = 550; // プレイヤーの位置X
	constexpr int kPlayerY       = 900; // プレイヤーの位置Y
	constexpr float kAnimSpeed   = 4.0f;// アニメーションスピード
	constexpr float kAnimFrame   = 8.0f;// アニメーションフレーム
	constexpr float kScrollSpeed = 3.0f;// スクロールスピード
}

SceneClear::SceneClear() :
	m_scrollX(0.0f),
	m_animCount(0),
	m_animFrame(0)
{
	m_bgmHandle       = LoadSoundMem("bgm/clear_bgm.mp3");// BGM
	m_bgHandle        = LoadGraph("data/clear3.png");     // クリア背景画像
	m_endHandle       = LoadGraph("data/endButton.png");  // 終了ボタン画像
	m_playerRunHandle = LoadGraph("data/player_move.png");// プレイヤー画像
	m_clearHandle = LoadGraph("data/spring_has_come.png");// クリア画像
	ChangeVolumeSoundMem(180, m_bgmHandle);
	PlaySoundMem(m_bgmHandle, DX_PLAYTYPE_LOOP);
	m_blinkAngle = 0.0f;
}

SceneClear::~SceneClear()
{
	StopSoundMem(m_bgmHandle);
	DeleteSoundMem(m_bgmHandle);
}

void SceneClear::Update()
{
	m_scrollX += kScrollSpeed;

	m_blinkAngle += 0.05f;

	int bgW, bgH;
	GetGraphSize(m_bgHandle, &bgW, &bgH);

	if(m_scrollX >= bgW)
	{
		m_scrollX -= bgW;
	}

	m_animCount++;
	if (m_animCount > kAnimSpeed)
	{
		m_animCount = 0;
		m_animFrame++;
		if (m_animFrame >= kAnimFrame)
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

	const int kFrameW = 144;
	const int kFrameH = 144;

	int srcX = m_animFrame * kFrameW;
	int srcY = 0;

	DrawRectRotaGraph(
		kPlayerX, kPlayerY,
		srcX, srcY,
		kFrameW, kFrameH,
		kPlayerScale,
		0.0f,
		m_playerRunHandle,
		true
	);
	DrawGraph(0, 0, m_clearHandle, true);
	// スタートボタンを点滅させる
	int alpha = static_cast<int>((sinf(m_blinkAngle) * 0.5f + 0.5f) * 255);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	DrawGraph(0, 0, m_endHandle, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

Scene* SceneClear::GetNextScene()
{
	return new SceneTitle();
}
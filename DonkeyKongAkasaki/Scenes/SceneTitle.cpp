#include "SceneTitle.h"
#include "../Systems/Pad.h"
#include "../Systems/Game.h"
#include "SceneMain.h"
#include <DxLib.h>
#include <EffekseerForDXLib.h>

SceneTitle::SceneTitle()
{
	// 画像
	m_titleHandle     = LoadGraph("data/title.png");      // タイトル画像
	m_titleLogoHandle = LoadGraph("data/title_logo.png"); // タイトルロゴ画像
	m_startHandle     = LoadGraph("data/press_start.png");// Start画像

	// BGM
	m_bgmHandle = LoadSoundMem("bgm/title_bgm.mp3");// タイトルbgm
	m_selectSe  = LoadSoundMem("bgm/select_se.mp3");// セレクトSE

	ChangeVolumeSoundMem(180, m_bgmHandle);
	PlaySoundMem(m_bgmHandle, DX_PLAYTYPE_LOOP);

	m_blinkAngle = 0.0f;

	m_sakuraEffectsHandle= LoadEffekseerEffect("data/sakura3.efkefc");// 桜のエフェクト
	// エフェクトを再生する。
	m_sakuraEffectsHandle = PlayEffekseer2DEffect(m_sakuraEffectsHandle);
	// Effekseerで作成したエフェクトは2D表示の場合、小さすぎることが殆どなので必ず拡大する。
	SetScalePlayingEffekseer2DEffect(m_sakuraEffectsHandle, 50.0f, 50.0f, 50.0f);
	// 再生中のエフェクトの位置
	SetPosPlayingEffekseer2DEffect(m_sakuraEffectsHandle, Game::kScreenWidth/2, Game::kScreenHeight / 2, 0);
}

SceneTitle::~SceneTitle()
{
	StopSoundMem(m_bgmHandle);
	DeleteSoundMem(m_bgmHandle);
	// エフェクトリソースを削除する。(Effekseer終了時に破棄されるので削除しなくてもいい)
	DeleteEffekseerEffect(m_sakuraEffectsHandle);
	DeleteGraph(m_startHandle);
	DeleteGraph(m_titleLogoHandle);
	DeleteGraph(m_titleHandle);
}

void SceneTitle::Update()
{
	// Effekseerにより再生中のエフェクトを更新する。
	UpdateEffekseer2D();

	m_blinkAngle += 0.05f;

	if (Pad::IsTrigger(PAD_INPUT_8))
	{
		PlaySoundMem(m_selectSe, DX_PLAYTYPE_BACK);
		m_isEnd = true;
	}
	if (Pad::IsTrigger(PAD_INPUT_1))
	{
		PlaySoundMem(m_selectSe, DX_PLAYTYPE_BACK);
		m_isEnd = true;
	}
}

void SceneTitle::Draw()
{
	DrawGraph(0, 0,m_titleHandle, true);
	// Effekseerにより再生中のエフェクトを描画する。
	DrawEffekseer2D();
	DrawGraph(0, 0,m_titleLogoHandle, true);
	
	// スタートボタンを点滅させる
	int alpha = static_cast<int>((sinf(m_blinkAngle) * 0.5f + 0.5f) * 255);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	DrawGraph(0, 0, m_startHandle, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

// 次のシーンに遷移する
Scene* SceneTitle::GetNextScene()
{
	return new SceneMain();
}

#include "SceneTitle.h"
#include "Pad.h"
#include "SceneMain.h"
#include <DxLib.h>
#include "EffekseerForDXLib.h"


namespace
{
	constexpr float kScreenWidth = 1920.0f;// スクリーンの幅
	constexpr float kScreenHeight = 1080.0f;// スクリーンの高さ

}


SceneTitle::SceneTitle()
{
	m_titleHandle = LoadGraph("data/TitleImage.png");
	m_sakuraEffectsHandle= LoadEffekseerEffect("data/sakura2.efk");
	// エフェクトを再生する。
	m_sakuraEffectsHandle = PlayEffekseer2DEffect(m_sakuraEffectsHandle);
	// Effekseerで作成したエフェクトは2D表示の場合、小さすぎることが殆どなので必ず拡大する。
	SetScalePlayingEffekseer2DEffect(m_sakuraEffectsHandle, 1.0f, 1.0f, 1.0f);
	// 再生中のエフェクトを移動
	SetPosPlayingEffekseer2DEffect(m_sakuraEffectsHandle, kScreenWidth/2, kScreenHeight/2, 0);
}

SceneTitle::~SceneTitle()
{
	// エフェクトリソースを削除する。(Effekseer終了時に破棄されるので削除しなくてもいい)
	DeleteEffekseerEffect(m_sakuraEffectsHandle);
}

void SceneTitle::Update()
{
	
	// Effekseerにより再生中のエフェクトを更新する。
	UpdateEffekseer2D();
	if (Pad::IsTrigger(PAD_INPUT_8))
	{
		m_isEnd = true;
	}
}

void SceneTitle::Draw()
{
	DrawString(400, 300, "TitleScene", GetColor(255, 255, 255));
	DrawGraph(0, 0,m_titleHandle, true);
	// Effekseerにより再生中のエフェクトを描画する。
	DrawEffekseer2D();
}

// 次のシーンに遷移する
Scene* SceneTitle::GetNextScene()
{
	return new SceneMain();
}

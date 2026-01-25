#pragma once
#include "Scene.h"
class SceneTitle : public Scene
{
public:
	SceneTitle();
	~SceneTitle();
	void Init() override {};
	void Update() override;
	void Draw() override;

	bool IsEnd()const override { return m_isEnd; }
	Scene* GetNextScene() override;

private:
	// シーンが終わったか
	bool m_isEnd = false;
	// タイトルの画像
	int m_titleHandle;
	// タイトルロゴの画像
	int m_titleLogoHandle;
	// 桜のエフェクト
	int m_sakuraEffectsHandle;
	// タイトルBGM
	int m_bgmHandle;

};


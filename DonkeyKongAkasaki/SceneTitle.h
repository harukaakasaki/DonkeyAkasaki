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
	bool m_isEnd = false;
	// タイトルの画像
	int m_titleHandle;
	// 桜のエフェクト
	int m_sakuraEffectsHandle;
};


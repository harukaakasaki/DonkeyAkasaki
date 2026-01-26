#pragma once
#include "Scene.h"
class SceneClear : public Scene
{
public:
	SceneClear();
	~SceneClear();
	void Init() override {};
	void Update() override;
	void Draw() override;

	bool IsEnd()const override { return m_isEnd; }
	Scene* GetNextScene() override;

private:
	bool m_isEnd = false;
	int m_bgmHandle;
	int m_bgHandle;
	float m_scrollX;
};


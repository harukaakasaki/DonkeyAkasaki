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
	int m_playerRunHandle;
	int m_bgmHandle;
	int m_bgHandle;
	int m_clearHandle;
	int m_endHandle;
	int m_animFrame;
	int m_animCount;
	float m_scrollX;
};


#pragma once
#include "Scene.h"
class SceneClear : public Scene
{
public:
	void Init() override {};
	void Update() override;
	void Draw() override;

	bool IsEnd()const override { return m_isEnd; }
	Scene* GetNextScene() override;

private:
	bool m_isEnd = false;
};


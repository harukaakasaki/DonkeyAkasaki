#pragma once
#include "Scene.h"
class SceneTitle : public Scene
{
public:
	SceneTitle();
	void Init() override {};
	void Update() override;
	void Draw() override;

	bool IsEnd()const override { return m_isEnd; }
	Scene* GetNextScene() override;

private:
	bool m_isEnd = false;
	// ƒ^ƒCƒgƒ‹‚Ì‰æ‘œ
	int m_titleHandle;
};


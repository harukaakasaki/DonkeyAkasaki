#pragma once
#include "Scene.h"
class SceneController
{
public:
	void Init();
	void Update();
	void Draw();

private:
	Scene* m_pScene = nullptr;
};


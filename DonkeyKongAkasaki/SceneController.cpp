#include "SceneController.h"
#include "SceneTitle.h"

void SceneController::Init()
{
	m_pScene = new SceneTitle();
	m_pScene->Init();
}

void SceneController::Update()
{
	m_pScene->Update();

	if (m_pScene->IsEnd())
	{
		Scene* next = m_pScene->GetNextScene();
		delete m_pScene;
		m_pScene = next;

		if (m_pScene)
		{
			m_pScene->Init();
		}
	}
}

void SceneController::Draw()
{
	m_pScene->Draw();
}

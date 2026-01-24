#include "SceneController.h"
#include "SceneTitle.h"
#include <DxLib.h>
#include "Game.h"

void SceneController::Init()
{
	m_pScene = new SceneTitle();
	m_pScene->Init();
}

void SceneController::Update()
{
	if (!m_isFade)
	{
		m_pScene->Update();

		if (m_pScene->IsEnd())
		{
			m_pNextScene = m_pScene->GetNextScene();
			
			m_isFade = true;
			m_isFadeOut = true;
			m_fadeAlpha = 0;
		}
	}

	else
	{
		if (m_isFadeOut)
		{
			// フェードアウト
			m_fadeAlpha += 5;
			if (m_fadeAlpha >= 255)
			{
				m_fadeAlpha = 255;

				// シーン切り替え
				delete m_pScene;
				m_pScene = m_pNextScene;
				m_pScene->Init();

				// フェードインへ移行
				m_isFadeOut = false;
			}
		}
		else
		{
			m_fadeAlpha -= 5;
			if (m_fadeAlpha <= 0)
			{
				m_fadeAlpha = 0;
				m_isFade = false;
			}
		}
	}

	

	
	
}

void SceneController::Draw()
{
	m_pScene->Draw();

	if (m_isFade)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeAlpha);
		DrawBox(0, 0,
			Game::kScreenWidth,Game::kScreenHeight,
			GetColor(0, 0, 0),
			TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}

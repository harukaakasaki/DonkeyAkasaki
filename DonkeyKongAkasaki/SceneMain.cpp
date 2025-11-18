#include "SceneMain.h"
#include "Game.h"
#include "Enemy.h"
#include <DxLib.h>
#include "Player.h"
#include "Vec2.h"
#include "Camera.h"
#include <memory>

/// <summary>
/// コンストラクタ
/// </summary>
SceneMain::SceneMain()
{
	
	m_pPlayer = new Player;
	m_pCamera = new Camera;
	m_pEnemys.resize(4);
}

/// <summary>
/// デストラクタ
/// </summary>
SceneMain::~SceneMain()
{
	delete m_pPlayer;
	delete m_pEnemy;
	delete m_pCamera;
}

/// <summary>
/// 初期化
/// </summary>
void SceneMain::Init()
{
	m_pPlayer->Init();

	m_pCamera->Init();
}

/// <summary>
/// 更新
/// </summary>
void SceneMain::Update()
{
	m_pPlayer->Update();
	m_pCamera->Update(*m_pPlayer);
}

/// <summary>
/// 描画
/// </summary>
void SceneMain::Draw()
{
	Vec2 cameraPos;
	cameraPos = m_pCamera->GetPos();

	DrawBox(Game::kScreenWidth-cameraPos.x,Game::kScreenHeight - cameraPos.y,
		0, 0, GetColor(0, 100, 100), true);
	DrawLine(0 - cameraPos.x, 640 - cameraPos.y, Game::kScreenWidth - cameraPos.x, 640 - cameraPos.y, GetColor(255, 255, 255));
	m_pPlayer->Draw(*m_pCamera);

}

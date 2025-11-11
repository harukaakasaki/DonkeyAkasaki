#include "SceneMain.h"
#include "Game.h"
#include "Enemy.h"
#include "DxLib.h"
#include "Player.h"

/// <summary>
/// コンストラクタ
/// </summary>
SceneMain::SceneMain()
{
	m_pPlayer = new Player;
	m_pEnemy = new Enemy;
}

/// <summary>
/// デストラクタ
/// </summary>
SceneMain::~SceneMain()
{
}

/// <summary>
/// 初期化
/// </summary>
void SceneMain::Init()
{
	m_pPlayer->Init();
	m_pEnemy->Init();
}

/// <summary>
/// 更新
/// </summary>
void SceneMain::Update()
{
	m_pPlayer->Update();
	m_pEnemy->Update();
}

/// <summary>
/// 描画
/// </summary>
void SceneMain::Draw()
{
	DrawLine(0, 640, Game::kScreenWidth, 640, GetColor(255, 255, 255));
	m_pPlayer->Draw();
	m_pEnemy->Draw();
	
}

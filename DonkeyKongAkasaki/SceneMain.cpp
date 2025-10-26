#include "SceneMain.h"
#include "Player.h"
#include "Enemy.h"

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
	m_pPlayer->Draw();
	m_pEnemy->Draw();
}

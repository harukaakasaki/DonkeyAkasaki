#include "SceneMain.h"
#include "Game.h"
#include "Enemy.h"
#include <DxLib.h>
#include "Player.h"
#include "Vec2.h"
#include "Camera.h"
#include <memory>
#include "EnemyBat.h"

namespace
{
	bool IsHitRect(const Rect& a, const Rect& b)
	{
		return !(a.right < b.left ||
			a.left > b.right ||
			a.bottom < b.top ||
			a.top > b.bottom);
	}
}

/// <summary>
/// コンストラクタ
/// </summary>
SceneMain::SceneMain()
{
	
	m_pPlayer = new Player;
	m_pEnemy = new Enemy;
	m_pEnemyBat = new EnemyBat;
	m_pCamera = new Camera;

}

/// <summary>
/// デストラクタ
/// </summary>
SceneMain::~SceneMain()
{
	delete m_pPlayer;
	delete m_pEnemy;
	delete m_pEnemyBat;
	delete m_pCamera;
}

/// <summary>
/// 初期化
/// </summary>
void SceneMain::Init()
{
	m_pPlayer->Init();
	m_pEnemy->Init();
	m_pEnemyBat->Init();
	m_pCamera->Init();
}



/// <summary>
/// 更新
/// </summary>
void SceneMain::Update()
{
	m_pPlayer->Update();
	m_pEnemy->Update();
	m_pEnemyBat->Update();
	m_pCamera->Update(*m_pPlayer);

	Rect playerHitBox = m_pPlayer->PlayerHitBox();
	Rect batBox       = m_pEnemyBat->EnemyBatHitBox();
	Rect playerAttack = m_pPlayer->AttackHitBox();

	if (IsHitRect(playerHitBox, batBox))
	{
		DrawString(50, 50, "当たってる！", GetColor(255, 0, 0));
	}

	if (m_pPlayer->IsAttack())
	{
		if (IsHitRect(playerAttack, batBox))
		{
			m_pEnemyBat->Kill(); // Enemy
			DrawString(100,100,"当たってる！",0U);
		}
	}
}



/// <summary>
/// 描画
/// </summary>
void SceneMain::Draw()
{
	Vec2 cameraPos;
	cameraPos = m_pCamera->GetPos();

    // 背景の表示（四角で色を付けているだけ）
	DrawBox(Game::kScreenWidth-cameraPos.x,Game::kScreenHeight - cameraPos.y,
		0, 0, GetColor(0, 100, 100), true);
	// 天井の線
	DrawLine(0 - cameraPos.x, 640 - cameraPos.y, Game::kScreenWidth - cameraPos.x, 640 - cameraPos.y, GetColor(255, 255, 255));
	// 地面の線
	DrawLine(0 - cameraPos.x, -10 - cameraPos.y, Game::kScreenWidth - cameraPos.x, -10 - cameraPos.y, GetColor(255, 255, 255));

	// プレイヤーの描画
	m_pPlayer->Draw(*m_pCamera);
	// エネミーの描画
	m_pEnemy->Draw(*m_pCamera);
	// コウモリの描画
	m_pEnemyBat->Draw(*m_pCamera);

}

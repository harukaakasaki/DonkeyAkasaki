#include "SceneMain.h"
#include "Game.h"
#include "Enemy.h"
#include "EnemyBat.h"
#include "EnemyMush.h"
#include "EnemyGolem.h"
#include <DxLib.h>
#include "Player.h"
#include "Vec2.h"
#include "Camera.h"
#include <memory>
#include "Bg.h"


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
	m_pEnemyMush = new EnemyMush;
	m_pEnemyGolem = new EnemyGolem;
	m_pCamera = new Camera;
	m_pBg = new Bg(m_pCamera);

}

/// <summary>
/// デストラクタ
/// </summary>
SceneMain::~SceneMain()
{
	delete m_pPlayer;
	delete m_pEnemy;
	delete m_pEnemyBat;
	delete m_pEnemyMush;
	delete m_pEnemyGolem;
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
	m_pEnemyMush->Init();
	m_pEnemyGolem->Init();
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
	m_pEnemyMush->Update();
	m_pEnemyGolem->Update();
	m_pCamera->Update(*m_pPlayer);
	m_pBg->Update();

	Rect playerHitBox = m_pPlayer->PlayerHitBox();
	Rect batBox       = m_pEnemyBat->EnemyBatHitBox();
	Rect mushBox      = m_pEnemyMush->EnemyMushHitBox();
	Rect golemBox     = m_pEnemyGolem->EnemyGolemHitBox();
	Rect playerAttack = m_pPlayer->AttackHitBox();

	if (m_pEnemyBat->IsAlive())
	{
		if (IsHitRect(playerHitBox, batBox))
		{
			m_isHitPlayer = true;
		}
	}
	
	if (m_pEnemyMush->IsAlive())
	{
		if (IsHitRect(playerHitBox, mushBox))
		{
			m_isHitPlayer = true;
		}
	}
	
	if (m_pEnemyGolem->IsAlive())
	{
		if (IsHitRect(playerHitBox, golemBox))
		{
			m_isHitPlayer = true;
		}
	}
	

	if (m_pPlayer->IsAttack()&&m_pEnemyBat->IsAlive())
	{
		if (IsHitRect(playerAttack, batBox))
		{
			m_pEnemyBat->Damage(); // Enemy
		}
	}

	if (m_pPlayer->IsAttack() && m_pEnemyMush->IsAlive())
	{
		if (IsHitRect(playerAttack, mushBox))
		{
			m_pEnemyMush->Damage(); // Enemy
		}
	}

	if (m_pPlayer->IsAttack() && m_pEnemyGolem->IsAlive())
	{
		if (IsHitRect(playerAttack, golemBox))
		{
			m_pEnemyGolem->Damage(); // Enemy
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
	// 背景の表示
	m_pBg->Draw();
	// 天井の線
	DrawLine(0 - cameraPos.x, 640 - cameraPos.y, 5000 - cameraPos.x, 640 - cameraPos.y, GetColor(255, 255, 255));
	// 地面の線
	DrawLine(0 - cameraPos.x, -10 - cameraPos.y, 5000 - cameraPos.x, -10 - cameraPos.y, GetColor(255, 255, 255));

	// プレイヤーの描画
	m_pPlayer->Draw(*m_pCamera);
	// エネミーの描画
	m_pEnemy->Draw(*m_pCamera);
	// コウモリの描画
	m_pEnemyBat->Draw(*m_pCamera);
	// キノコの描画
	m_pEnemyMush->Draw(*m_pCamera);
	// ゴーレムの描画
	m_pEnemyGolem->Draw(*m_pCamera);
	

	if (m_isHitPlayer)
	{
		DrawString(800, 300, "めっちゃ痛い", GetColor(255, 0, 0));
	}

}

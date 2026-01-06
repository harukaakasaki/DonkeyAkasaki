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
	delete m_pCamera;
}

/// <summary>
/// 初期化
/// </summary>
void SceneMain::Init()
{
	m_pPlayer->Init();
	m_pEnemy->Init();
	m_pCamera->Init();

	// コウモリ
	std::vector<Vec2>batPosition =
	{
		{400.0f,400.0f},
		{800.0f,420.0f},
		{1200.0f,450.0f}
	};

	for (auto& pos : batPosition)
	{
		auto bat = std::make_unique<EnemyBat>();
		bat->Init();
		bat->SetPos(pos);
		m_enemyBats.push_back(std::move(bat));
	}

	// キノコ
	std::vector<Vec2>mushPosition =
	{
		{900.0f,550.0f},
		{1700.0f,550.0f},
		{4000.0f,550.0f}
	};

	for (auto& pos : mushPosition)
	{
		auto mush = std::make_unique<EnemyMush>();
		mush->Init();
		mush->SetPos(pos);
		m_enemyMushes.push_back(std::move(mush));
	}

	std::vector<Vec2>golemPosition =
	{
		{4500.0f,550.0f}
	};

	for (auto& pos : golemPosition)
	{
		auto golem = std::make_unique<EnemyGolem>();
		golem->Init();
		golem->SetPos(pos);
		m_enemyGolems.push_back(std::move(golem));
	}
}



/// <summary>
/// 更新
/// </summary>
void SceneMain::Update()
{
	m_pPlayer->Update();
	m_pEnemy->Update();
	for (auto& bat : m_enemyBats)
	{
		bat->Update();
	}

	for (auto& mush : m_enemyMushes)
	{
		mush->Update();
	}

	for (auto& golem : m_enemyGolems)
	{
		golem->Update();
	}
	m_pCamera->Update(*m_pPlayer);
	m_pBg->Update();



	Rect playerRect = m_pPlayer->GetRect();
	Rect chipRect;

	if (m_pBg->IsCollision(playerRect, chipRect))
	{
		m_pPlayer->ResolveCollision(chipRect);
	}

	// プレイヤーとエネミーの当たり判定
	CheckPlayerEnemyCollision();
	// プレイヤーの攻撃判定
	CheckPlayerAttackCollision();

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
	//DrawLine(0 - cameraPos.x, 640 - cameraPos.y, 5000 - cameraPos.x, 640 - cameraPos.y, GetColor(255, 255, 255));
	// 地面の線
	DrawLine(0 - cameraPos.x, -10 - cameraPos.y, 5000 - cameraPos.x, -10 - cameraPos.y, GetColor(255, 255, 255));

	// プレイヤーの描画
	m_pPlayer->Draw(*m_pCamera);
	m_pPlayer->DrawHP();
	// エネミーの描画
	m_pEnemy->Draw(*m_pCamera);
	// コウモリの描画
	for (auto& bat : m_enemyBats)
	{
		bat->Draw(*m_pCamera);
	}
	// キノコの描画
	for (auto& mush : m_enemyMushes)
	{
		mush->Draw(*m_pCamera);
	}
	// ゴーレムの描画
	for (auto& golem : m_enemyGolems)
	{
		golem->Draw(*m_pCamera);
	}
	
#ifdef _DEBUG

	if (m_isHitPlayer)
	{
		DrawString(800, 300, "当たってる", GetColor(255, 0, 0));
	}

#endif
}

void SceneMain::CheckPlayerEnemyCollision()
{
	Rect playerBox = m_pPlayer->PlayerHitBox();

	// コウモリ
	for (auto& bat : m_enemyBats)
	{
		if (!bat->IsAlive())continue;

		if (IsHitRect(playerBox, bat->EnemyBatHitBox()))
		{
			float dir = (m_pPlayer->GetPos().x < bat->GetPos().x)
				? -1.0f
				: 1.0f;

			m_isHitPlayer = true;
			m_pPlayer->Damage(dir);
		}
	}

	// キノコ
	for (auto& mush : m_enemyMushes)
	{
		if (!mush->IsAlive())continue;

		if (IsHitRect(playerBox, mush->EnemyMushHitBox()))
		{
			float dir = (m_pPlayer->GetPos().x < mush->GetPos().x)
				? -1.0f
				: 1.0f;

			m_isHitPlayer = true;
			m_pPlayer->Damage(dir);
		}
	}

	// ゴーレム
	for (auto& golem : m_enemyGolems)
	{
		if (!golem->IsAlive())continue;

		if (IsHitRect(playerBox, golem->EnemyGolemHitBox()))
		{
			float dir = (m_pPlayer->GetPos().x < golem->GetPos().x)
				? -1.0f
				: 1.0f;

			m_isHitPlayer = true;
			m_pPlayer->Damage(dir);
		}
	}

}

void SceneMain::CheckPlayerAttackCollision()
{
	if (!m_pPlayer->IsAttack())return;

	Rect attackBox = m_pPlayer->AttackHitBox();

	// コウモリ
	for (auto& bat : m_enemyBats)
	{
		if (!bat->IsAlive())continue;
		if (IsHitRect(attackBox, bat->EnemyBatHitBox()))
		{
			bat->Damage(); // Enemy
		}
	}

	// キノコ
	for (auto& mush : m_enemyMushes)
	{
		if (!mush->IsAlive())continue;
		if (IsHitRect(attackBox, mush->EnemyMushHitBox()))
		{
			mush->Damage(); // Enemy
		}
	}

	// ゴーレム
	for (auto& golem : m_enemyGolems)
	{
		if (!golem->IsAlive())continue;
		if (IsHitRect(attackBox, golem->EnemyGolemHitBox()))
		{
			golem->Damage(); // Enemy
		}
	}
}

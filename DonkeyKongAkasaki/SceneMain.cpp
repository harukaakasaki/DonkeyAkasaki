#include "SceneClear.h"
#include "SceneMain.h"
#include "Game.h"
#include "Enemy.h"
#include "EnemyBat.h"
#include "EnemyMush.h"
#include "EnemyGolem.h"
#include <DxLib.h>
#include "Player.h"
#include "Pad.h"
#include "Vec2.h"
#include "Camera.h"
#include <memory>
#include "Bg.h"


namespace
{
	constexpr float kGoalX = 25000.0f;// ゴール位置
	constexpr float kGoalWidth = 128.0f;// ゴール位置幅
	constexpr int ktreeX = 24700; // 桜位置X
	constexpr int ktreeY = 220;  // 桜位置Y

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
	m_bgmHandle = LoadSoundMem("bgm/game_bgm2.mp3");
	ChangeVolumeSoundMem(180, m_bgmHandle);
	PlaySoundMem(m_bgmHandle, DX_PLAYTYPE_LOOP);
	m_treeHandle = LoadGraph("data/sakuratree.png");
}

/// <summary>
/// デストラクタ
/// </summary>
SceneMain::~SceneMain()
{
	delete m_pPlayer;
	delete m_pEnemy;
	delete m_pCamera;
	DeleteGraph(m_treeHandle);
	StopSoundMem(m_bgmHandle);
	DeleteSoundMem(m_bgmHandle);
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
		{7000.0f,800.0f},
		{7700.0f,700.0f},
		{8700.0f,820.0f},
		{9600.0f,650.0f},
		{18000.0f,200.0f},
		{16000.0f,700.0f},
		{17300.0f,400.0f},
		{12500.0f,780.0f}
	};
	// コウモリのスポーン地点
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
		{13000.0f,805.0f},
		{14000.0f,805.0f},
		{14500.0f,805.0f},
		{15500.0f,805.0f},
		{16500.0f,805.0f},
		{17000.0f,615.0f},
		{17800.0f,230.0f}
	
	};

	// キノコのスポーン地点
	for (auto& pos : mushPosition)
	{
		auto mush = std::make_unique<EnemyMush>();
		mush->Init();
		mush->SetPos(pos);
		m_enemyMushes.push_back(std::move(mush));
	}
	// ゴーレムのスポーン地点
	std::vector<Vec2>golemPosition =
	{
		{22000.0f,750.0f}
	};
	// ゴーレムのスポーン地点
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

	if (m_pPlayer->IsJustRespawn())
	{
		m_isReset = true;
		m_pPlayer->ClearJustRespawn();
	}
	
	// ヒットストップ
	/*if (m_hitStopFrame > 0)
	{
		m_hitStopFrame--;
		return;
	}*/
	// Playerがヒットしたら画面が揺れる
	if (m_pPlayer->IsDamage())
	{
		m_pCamera->Shake(30, 10.0f);// 揺れる強さ（時間,揺れ）
		m_pPlayer->ClearDamage();// 元に戻す
	}

	

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
	// ゴールの矩形
	Rect goalRect;
	goalRect.left = kGoalX;
	goalRect.right = kGoalX + kGoalWidth;
	goalRect.top = 0.0f;
	goalRect.bottom = 1080.0f;

	Rect playerRect = m_pPlayer->GetRect();
	Rect chipRect;

	// Playerとゴールの当たり判定
	if (IsHitRect(playerRect, goalRect))
	{
		m_isGoal = true;
	}

	if (m_pBg->IsCollision(playerRect, chipRect))
	{
		m_pPlayer->ResolveCollision(chipRect);
	}

	// プレイヤーとエネミーの当たり判定
	CheckPlayerEnemyCollision();
	// プレイヤーの攻撃判定
	CheckPlayerAttackCollision();

	if (m_isReset)
	{
		ResetEnemies();
		m_isReset = false;
	}
}

/// <summary>
/// 描画
/// </summary>
void SceneMain::Draw()
{
	// カメラのポジション
	Vec2 cameraPos;
	cameraPos = m_pCamera->GetPos();
	// 背景の表示
	m_pBg->Draw();
	// 天井の線
	//DrawLine(0 - cameraPos.x, 640 - cameraPos.y, 5000 - cameraPos.x, 640 - cameraPos.y, GetColor(255, 255, 255));
	// 地面の線
	DrawLine(0 - cameraPos.x, -10 - cameraPos.y, 5000 - cameraPos.x, -10 - cameraPos.y, GetColor(255, 255, 255));

	
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

	// プレイヤーの描画
	m_pPlayer->Draw(*m_pCamera);
	m_pPlayer->DrawHP();

	// ゴール画像の描画
	DrawGraph(
		static_cast<int>(ktreeX-cameraPos.x), 
		static_cast<int>(ktreeY-cameraPos.y), 
		m_treeHandle, true);

	
#ifdef _DEBUG

	if (Pad::IsTrigger(PAD_INPUT_8))
	{
		m_isGoal = true;
	}

	int drawX = static_cast<int>(kGoalX - cameraPos.x);
	DrawBox(drawX, 0, drawX + kGoalWidth, 1080, GetColor(255, 255, 0), false);
	// クリアシーンができたら#ifdefに移動
	if (m_isGoal)
	{
		DrawString(drawX - 10, 200, "クリア！！！", GetColor(255, 255, 0));
	}
	if (m_isHitPlayer)
	{
		DrawString(800, 300, "当たってる", GetColor(255, 0, 0));
	}

#endif
}

// 画面を止める（ヒットストップ）
void SceneMain::HitStop(int frame)
{
	m_hitStopFrame = frame;
}
bool SceneMain::IshitStop() const
{
	return m_hitStopFrame > 0;
}

// 次のシーンに遷移する
bool SceneMain::IsEnd() const
{
	return m_isGoal;
}
Scene* SceneMain::GetNextScene()
{
	return new SceneClear();
}

// プレイヤーとエネミーの当たり判定
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
			m_pPlayer->Damage(dir);

			HitStop(3);
		}
	}

	// キノコ
	for (auto& mush : m_enemyMushes)
	{
		

		if (IsHitRect(playerBox, mush->EnemyMushHitBox()))
		{
			if (!mush->IsAlive())continue;
			float dir = (m_pPlayer->GetPos().x < mush->GetPos().x)
				? -1.0f
				: 1.0f;
			m_pPlayer->Damage(dir);

			HitStop(3);
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
			m_pPlayer->Damage(dir);

			HitStop(3);
		}
	}

}

// プレイヤーの攻撃とエネミーの当たり判定
void SceneMain::CheckPlayerAttackCollision()
{
	if (!m_pPlayer->IsAttackHitActive())return;

	Rect attackBox = m_pPlayer->AttackHitBox();

	// コウモリ
	for (auto& bat : m_enemyBats)
	{
		if (!bat->IsAlive())continue;
		if (IsHitRect(attackBox, bat->EnemyBatHitBox()))
		{
			bat->Damage(); // Enemy
			HitStop(3);
		}
	}

	// キノコ
	for (auto& mush : m_enemyMushes)
	{
		if (!mush->IsAlive())continue;
		if (IsHitRect(attackBox, mush->EnemyMushHitBox()))
		{
			mush->Damage(); // Enemy
			HitStop(3);
		}
	}

	// ゴーレム
	for (auto& golem : m_enemyGolems)
	{
		if (!golem->IsAlive())continue;
		if (IsHitRect(attackBox, golem->EnemyGolemHitBox()))
		{
			golem->Damage(); // Enemy
			HitStop(3);
		}
	}
}

// ポジションのリセット
void SceneMain::ResetEnemies()
{
	m_enemyBats.clear();
	m_enemyMushes.clear();
	m_enemyGolems.clear();

	std::vector<Vec2>batPosition =
	{
		{7000.0f,800.0f},
		{7700.0f,700.0f},
		{8700.0f,820.0f},
		{9600.0f,650.0f},
		{18000.0f,200.0f},
		{16000.0f,700.0f},
		{17300.0f,400.0f},
		{12500.0f,780.0f}
	};
	for (auto& pos : batPosition)
	{
		auto bat = std::make_unique<EnemyBat>();
		bat->Init();
		bat->SetPos(pos);
		m_enemyBats.push_back(std::move(bat));
	}

	std::vector<Vec2>mushPosition =
	{
		{13000.0f,805.0f},
		{14000.0f,805.0f},
		{14500.0f,805.0f},
		{15500.0f,805.0f},
		{16500.0f,805.0f},
		{17000.0f,615.0f},
		{17800.0f,230.0f}
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
		{22000.0f,750.0f}
	};
	for (auto& pos : golemPosition)
	{
		auto golem = std::make_unique<EnemyGolem>();
		golem->Init();
		golem->SetPos(pos);
		m_enemyGolems.push_back(std::move(golem));
	}
}

#pragma once
#include <vector>
#include <memory>
#include "Scene.h"

// プロトタイプ宣言
class Player;
class Enemy;
class EnemyBat;
class EnemyMush;
class EnemyGolem;
class Camera;
class Bg;

class SceneMain : public Scene
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	SceneMain();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~SceneMain();

	/// <summary>
	/// 初期化
	/// </summary>
	void Init();
	/// <summary>
	/// 更新
	/// </summary>
	void Update();
	/// <summary>
	/// 描画
	/// </summary>
	void Draw();
	/// <summary>
	/// ヒットストップ
	/// </summary>
	/// <param name="frame"></param>
	void HitStop(int frame);
	bool IshitStop()const;

	bool IsEnd() const override;
	Scene* GetNextScene() override;


	

private:
	int m_hitStopFrame = 0;
	// Playerクラスのポインタを取得した
	Player* m_pPlayer;
	// Enemyクラスのポインタを取得した
	Enemy* m_pEnemy;
	// EnemyBatクラスのポインタを取得した
	std::vector<std::unique_ptr<EnemyBat>> m_enemyBats;// unique_ptr = deleteしなくていい安全なポインタ
	// EnemyMushクラスのポインタを取得した
	std::vector<std::unique_ptr<EnemyMush>> m_enemyMushes;
	// EnemyGolemクラスのポインタを取得した
	std::vector<std::unique_ptr<EnemyGolem>> m_enemyGolems;
	// Cameraクラスのポインタを取得した
	Camera* m_pCamera;
	// Bgクラスのポインタを取得した
	Bg* m_pBg;

	void CheckPlayerEnemyCollision();
	void CheckPlayerAttackCollision();

	bool m_isHitPlayer = false; 
	bool m_isGoal = false;

//	std::vector<std::shared_ptr<Enemy>>m_pEnemys;
};


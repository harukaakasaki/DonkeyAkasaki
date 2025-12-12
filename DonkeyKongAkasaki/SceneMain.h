#pragma once
#include <vector>
#include <memory>

// プロトタイプ宣言
class Player;
class Enemy;
class EnemyBat;
class EnemyMush;
class EnemyGolem;
class Camera;
class Bg;

class SceneMain
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

	

private:
	// Playerクラスのポインタを取得した
	Player* m_pPlayer;
	// Enemyクラスのポインタを取得した
	Enemy* m_pEnemy;
	// EnemyBatクラスのポインタを取得した
	EnemyBat* m_pEnemyBat;
	// EnemyMushクラスのポインタを取得した
	EnemyMush* m_pEnemyMush;
	// EnemyGolemクラスのポインタを取得した
	EnemyGolem* m_pEnemyGolem;
	// Cameraクラスのポインタを取得した
	Camera* m_pCamera;
	// Bgクラスのポインタを取得した
	Bg* m_pBg;

	bool m_isHitPlayer = false; 

//	std::vector<std::shared_ptr<Enemy>>m_pEnemys;
};


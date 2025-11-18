#pragma once
#include <vector>
#include <memory>

// プロトタイプ宣言
class Player;
class Enemy;
class Camera;

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
	// Cameraクラスのポインタを取得した
	Camera* m_pCamera;

	std::vector<std::shared_ptr<Enemy>>m_pEnemys;
};


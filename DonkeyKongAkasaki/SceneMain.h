#pragma once
class Player;
class Enemy;
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
	Player* m_pPlayer;
	Enemy* m_pEnemy;
};


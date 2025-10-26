#pragma once
class Player;
class Enemy;
class SceneMain
{
public:
	SceneMain();
	~SceneMain();

	void Init();
	void Update();
	void Draw();

private:
	Player* m_pPlayer;
	Enemy* m_pEnemy;
};


#include "Enemy.h"
#include "Character.h"
#include "SceneMain.h"
#include "Vec2.h"
#include <DxLib.h>

/// <summary>
/// コンストラクタ
/// </summary>
Enemy::Enemy()
{
	m_handle = LoadGraph("data/bat.png"); 
}

/// <summary>
/// デストラクタ
/// </summary>
Enemy::~Enemy()
{
	DeleteGraph(m_handle);
}



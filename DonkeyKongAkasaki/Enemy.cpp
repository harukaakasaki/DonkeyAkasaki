#include "Enemy.h"
#include "DxLib.h"

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

/// <summary>
/// 初期化
/// </summary>
void Enemy::Init()
{
}

/// <summary>
/// 更新
/// </summary>
void Enemy::Update()
{
}

/// <summary>
/// 描画
/// </summary>
void Enemy::Draw()
{
	DrawGraph(0, 150, m_handle, true);
}

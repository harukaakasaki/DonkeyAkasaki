#include <cmath>
#include <DxLib.h>
#include "Camera.h"
#include "Game.h"
#include "Character.h"
#include "Player.h"

// ラープ
// 滑らかに動くようにする
Vec2 VLerp(Vec2 start, Vec2 end, float t)
{
	Vec2 ret;
	ret.x = std::lerp(start.x, end.x, t);
	ret.y = std::lerp(start.y, end.y, t);
	return ret;

}


Camera::Camera():
	m_pos{0,0},
	drawOffset{0,0}
{
}

Camera::~Camera()
{
}

void Camera::Init()
{
	m_pos = { 0, 0 };
}

void Camera::Update(Player& player)
{
	// プレイヤー位置の取得
	Vec2 playerPos = player.GetPos();

	// カメラの次のポジション
	Vec2 nextPos;
	nextPos.x = playerPos.x - Game::kScreenWidth / 2;
	nextPos.y = playerPos.y - (Game::kScreenHeight / 2 + 200);// プレイヤーの位置（真ん中）よりも少し下げる


	m_pos = VLerp(m_pos,nextPos,1.0f);

}

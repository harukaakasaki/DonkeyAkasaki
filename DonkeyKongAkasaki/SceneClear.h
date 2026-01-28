#pragma once
#include "Scene.h"
class SceneClear : public Scene
{
public:
	SceneClear();
	~SceneClear();
	void Init() override {};
	void Update() override;
	void Draw() override;

	bool IsEnd()const override { return m_isEnd; }
	Scene* GetNextScene() override;

private:
	// シーンの切り替え
	bool m_isEnd = false;
	// プレイヤー走り画像
	int m_playerRunHandle;
	// BGM
	int m_bgmHandle;
	// 背景画像
	int m_bgHandle;
	// クリア画像
	int m_clearHandle;
	// 終了画像
	int m_endHandle;
	// アニメフレーム
	int m_animFrame;
	// アニメカウント
	int m_animCount;
	// スクロール（横）
	float m_scrollX;
	// 点滅アングル
	float m_blinkAngle;
};


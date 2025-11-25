#pragma once

// エネミーベースの制作完了
// 次に3種類のエネミーを作りたい

#include "Camera.h"
#include "Character.h"
class Enemy:public Character
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Enemy();
	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~Enemy();
	/// <summary>
	/// 初期化
	/// </summary>
	virtual void Init();
	/// <summary>
	/// 更新
	/// </summary>
	virtual void Update();
	/// <summary>
	/// 描画
	/// </summary>
	virtual void Draw(const Camera& camera);

private:

};


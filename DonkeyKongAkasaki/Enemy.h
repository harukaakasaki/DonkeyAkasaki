#pragma once
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
	virtual ~Enemy()override;

	/// <summary>
	/// 初期化
	/// </summary>
	virtual void Init()override;
	/// <summary>
	/// 更新
	/// </summary>
	virtual void Update()override;
	/// <summary>
	/// 描画
	/// </summary>
	virtual void Draw()override;

private:

};


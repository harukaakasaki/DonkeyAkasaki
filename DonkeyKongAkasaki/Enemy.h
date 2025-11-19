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
	virtual ~Enemy();
	virtual void Init();
	virtual void Update();
	virtual void Draw();

private:

};


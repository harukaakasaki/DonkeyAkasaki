#pragma once
#include "Character.h"
class Enemy:public Character
{
public:
	Enemy();
	virtual ~Enemy()override;

	virtual void Init()override;
	virtual void Update()override;
	virtual void Draw()override;

private:

};


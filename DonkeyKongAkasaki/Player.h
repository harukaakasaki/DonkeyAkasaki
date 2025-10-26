#pragma once
#include "Character.h"
class Player: public Character
{
public:
	Player();
	virtual ~Player()override;

	virtual void Init()override;
	virtual void Update()override;
	virtual void Draw()override;

private:
	int x;
	int y;
};


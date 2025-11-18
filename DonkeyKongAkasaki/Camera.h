#pragma once
#include"Vec2.h"

class Player;
class Camera
{
public:
	Camera();
	~Camera();
	void Init();
	void Update(Player& player);
	
	Vec2 GetPos() { return m_pos; };

private:
	Vec2 m_pos;
	Vec2 drawOffset;
};




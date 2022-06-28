#pragma once
#include "Enemy.h"
class Enemy3 :
	public Enemy
{
private:

	float	damage = 30.0, health = 70.0;
	float	speed = 0.5;
	hgeRect	rect;

public:
	Enemy3(float, float, float);
	~Enemy3();

	void render();
	void move(float);

	hgeRect getRect() { return rect; }
	float getDamage() { return damage; }
	float getHealth() { return health; }
	void setHealth(float h) { health = h; }
};


#pragma once
#include "Enemy.h"
class Enemy2 :
	public Enemy
{
private:

	float	damage = 10.0, health = 30.0;
	float	speed = 0.5;
	hgeRect	rect;

public:
	Enemy2(float, float, float);
	~Enemy2();

	void render();
	void move(float);

	hgeRect getRect() { return rect; }
	float getDamage() { return damage; }
	float getHealth() { return health; }
	void setHealth(float h) { health = h; }
};


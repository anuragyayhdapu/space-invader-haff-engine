#pragma once
#include "Enemy.h"
class Enemy1 :
	public Enemy
{
private:

	float	damage = 5.0, health = 20.0;
	float	speed = 0.5;
	hgeRect	rect;

public:
	Enemy1(float, float, float);
	~Enemy1();

	void render();
	void move(float);

	hgeRect getRect() { return rect; }
	float getDamage() { return damage; }
	float getHealth() { return health; }
	void setHealth(float h) { health = h; }
};


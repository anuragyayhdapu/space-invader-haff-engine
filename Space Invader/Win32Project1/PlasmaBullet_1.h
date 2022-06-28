#pragma once
#include "Bullet.h"
class PlasmaBullet_1 : public Bullet
{
private:

	float		damage = 5.0;
	const float	speed = 10.0;
	hgeRect		rect;

public:
	PlasmaBullet_1(float, float);
	~PlasmaBullet_1();

	void render();
	void move();
	hgeRect getRect() { return rect; }
	float getDamage() { return damage; }
};


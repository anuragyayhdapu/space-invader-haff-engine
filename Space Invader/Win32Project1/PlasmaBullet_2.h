#pragma once
#include "Bullet.h"
class PlasmaBullet_2 :
	public Bullet
{
private:
	float damage = 15.0;
	const float speed = 10.0;
	hgeRect rect;

public:
	PlasmaBullet_2(float, float);
	~PlasmaBullet_2();

	void render();
	void move();
	hgeRect getRect() { return rect; }
	float getDamage() { return damage; }
};


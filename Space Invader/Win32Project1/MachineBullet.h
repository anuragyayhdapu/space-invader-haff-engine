#pragma once

#include "Bullet.h" 

class MachineBullet : public Bullet
{
private:

	float		damage = 5.0;
	const float	speed = 10.0;
	hgeRect		rect, rect2;
 
public:
	MachineBullet(float, float);
	~MachineBullet();

	void render();
	void move();
	hgeRect getRect() { return rect; }
	hgeRect getRect2() { return rect2; }
	float getDamage() { return damage; }
};


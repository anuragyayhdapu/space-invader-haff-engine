#pragma once
#include "Bullet.h"
class Fireball :
	public Bullet
{
private:

	float damage = 20.0;
	const float speed = 8.0;
	hgeRect rect;
	hgeAnimation* fireball_anim;

public:
	Fireball(float, float);
	~Fireball();

	void move();
	void render(float dt);
	hgeRect getRect() { return rect; }
	float getDamage() { return damage; }
};


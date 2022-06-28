#pragma once
#include "Bullet.h"
class Rocket :
	public Bullet
{
private:

	float damage = 35.0;
	const float speed = 3.0;
	hgeRect rect;
	hgeAnimation* rocket_anim;

public:
	Rocket(float, float);
	~Rocket();

	void move();
	void render(float dt);
	hgeRect getRect() { return rect; }
	float getDamage() { return damage; }
};


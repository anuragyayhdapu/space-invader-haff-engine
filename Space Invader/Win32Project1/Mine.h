#pragma once
#include "Bullet.h"
class Mine :
	public Bullet
{
private:

	float damage = 35.0;
	const float speed = 3.0;
	hgeRect rect;
	hgeAnimation* mine_anim; 

public:
	Mine(float, float);
	~Mine();

	void move();
	void render(float dt);
	hgeRect getRect() { return rect; }
	float getDamage() { return damage; }
};


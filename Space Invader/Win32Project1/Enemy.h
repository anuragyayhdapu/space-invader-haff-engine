#pragma once

#include <hge.h>
#include <hgeresource.h>
#include <hgesprite.h>

class Enemy
{
protected:
	HGE					*e_hge;
	hgeSprite			*enemySprite;
	hgeResourceManager  *enemyResManager;
	float				en_x, en_y;

public:

	Enemy(float, float);
	~Enemy();

	void move(float);
	void render(float, float);

	float getenemy_x() { return en_x; }
	float getenemy_y() { return en_y; }
};


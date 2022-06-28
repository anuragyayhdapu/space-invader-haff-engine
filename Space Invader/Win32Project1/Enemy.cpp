#include "Enemy.h"


Enemy::Enemy(float posx, float posy)
{
	e_hge = hgeCreate(HGE_VERSION);
	enemyResManager = new hgeResourceManager("resource.res");

	en_x = posx;
	en_y = posy;
}


Enemy::~Enemy()
{
}


void Enemy::render(float, float)
{
	enemySprite->Render(en_x, en_y);
}


void Enemy::move(float speed)
{
	en_y += speed;
}
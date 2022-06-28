#include "Enemy1.h"
#include <random>


Enemy1::Enemy1(float posx, float posy, float fuel) :Enemy(posx, posy)
{
	enemySprite = enemyResManager->GetSprite("enemy1_sprite");
	enemySprite->SetHotSpot(30, 20);
}


Enemy1::~Enemy1()
{
	delete enemyResManager;
	e_hge->Release();
}

void Enemy1::render()
{
	Enemy::render(en_x, en_y);
}

void Enemy1::move(float fuel)
{
	if (e_hge->Input_GetKeyState(HGEK_SHIFT) && fuel > 50.0)
		speed = 6.0;
	else if (e_hge->Input_GetKeyState(HGEK_UP) && fuel > 0.0)
		speed = 4.0;
	else if (e_hge->Input_GetKeyState(HGEK_DOWN))
		speed = 0.5;
	else
		//speed = 0.5;
		speed = 0.3f + static_cast <float> (rand()) / static_cast <float> (RAND_MAX / 0.5);

	Enemy::move(speed);
	enemySprite->GetBoundingBox(en_x, en_y, &rect);
}
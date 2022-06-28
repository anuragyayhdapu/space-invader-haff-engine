#include "Enemy3.h"


Enemy3::Enemy3(float posx, float posy, float fuel) :Enemy(posx, posy)
{
	enemySprite = enemyResManager->GetSprite("enemy3_sprite");
	enemySprite->SetHotSpot(63, 126);
}


Enemy3::~Enemy3()
{
	delete enemyResManager;
	e_hge->Release();
}

void Enemy3::render()
{
	Enemy::render(en_x, en_y);
}

void Enemy3::move(float fuel)
{
	if (e_hge->Input_GetKeyState(HGEK_SHIFT) && fuel > 50.0)
		speed = 6.0;
	else if (e_hge->Input_GetKeyState(HGEK_UP) && fuel > 0.0)
		speed = 4.0;
	else if (e_hge->Input_GetKeyState(HGEK_DOWN))
		speed = 0.25;
	else
		//speed = 0.5;
		speed = 0.5f + static_cast <float> (rand()) / static_cast <float> (RAND_MAX / 2.0);

	Enemy::move(speed);
	enemySprite->GetBoundingBox(en_x, en_y, &rect);
}
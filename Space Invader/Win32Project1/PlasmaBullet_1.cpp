#include "PlasmaBullet_1.h"

/*
	Primary Weapon
	- Blue explosion
*/

PlasmaBullet_1::PlasmaBullet_1(float posx, float posy) : Bullet(posx, posy)
{
	bulletSprite = bulletResManger->GetSprite("plasma_bullet_sprite");
	bulletSprite->SetHotSpot(7.5, 2);
}


PlasmaBullet_1::~PlasmaBullet_1()
{
	delete bulletResManger;
	b_hge->Release();
}

void PlasmaBullet_1::render()
{
	Bullet::render(bx, by);
}

void PlasmaBullet_1::move()
{
	Bullet::move(PlasmaBullet_1::speed);				
	bulletSprite->GetBoundingBox(bx, by, &rect);
}
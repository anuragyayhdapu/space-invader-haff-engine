#include "PlasmaBullet_2.h"


PlasmaBullet_2::PlasmaBullet_2(float posx, float posy) : Bullet(posx, posy)
{
	bulletSprite = bulletResManger->GetSprite("plasma2_sprite");
	bulletSprite->SetHotSpot(0, 0);
}


PlasmaBullet_2::~PlasmaBullet_2()
{
	delete bulletResManger;
	b_hge->Release();
}

void PlasmaBullet_2::render()
{
	Bullet::render(bx, by);
}

void PlasmaBullet_2::move()
{
	Bullet::move(PlasmaBullet_2::speed);
	bulletSprite->GetBoundingBox(bx, by, &rect);
}
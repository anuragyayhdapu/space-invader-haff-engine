#include "MachineBullet.h"

/*
	Primary weapon
	1. Low damage
	2. High firing rate
	3. Blue explosions
	4. Low size, mass
*/

MachineBullet::MachineBullet(float posx, float posy) : Bullet(posx, posy)
{
	bulletSprite = bulletResManger->GetSprite("machine_bullet_sprite");
	bulletSprite->SetHotSpot(4, 0);
}


MachineBullet::~MachineBullet()
{
	delete bulletResManger;
	b_hge->Release();
}

void MachineBullet::render()
{
	Bullet::render(bx, by);
	Bullet::render(bx + 20, by);
}

void MachineBullet::move()
{
	Bullet::move(MachineBullet::speed);				// move 
	bulletSprite->GetBoundingBox(bx, by, &rect);	// returns the sprite bounding box
	bulletSprite->GetBoundingBox(bx + 20, by, &rect2); 
}
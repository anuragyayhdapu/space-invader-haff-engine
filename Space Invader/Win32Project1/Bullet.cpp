#include "Bullet.h"


Bullet::Bullet(float posx, float posy)
{
	b_hge = hgeCreate(HGE_VERSION);
	bulletResManger = new hgeResourceManager("resource.res");

	bx = posx;
	by = posy;
}

Bullet::~Bullet()
{
}

void Bullet::move(const float speed)
{
	by -= speed;
}

void Bullet::render(float posx, float posy)
{
	bulletSprite->Render(posx, posy);
}

 

// Make a parent bullet class, derive all bullets from that class
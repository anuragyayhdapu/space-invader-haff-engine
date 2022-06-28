#include "Fireball.h"


Fireball::Fireball(float posx, float posy) : Bullet(posx, posy)
{
	fireball_anim = bulletResManger->GetAnimation("fireball_anim");
	fireball_anim->SetHotSpot(0, 0);
	fireball_anim->Play();
}


Fireball::~Fireball()
{
	delete bulletResManger;
	b_hge->Release();
}

void Fireball::render(float dt)
{
	fireball_anim->Update(dt);
	fireball_anim->Render(bx, by);
}

void Fireball::move()
{
	Bullet::move(Fireball::speed);
	fireball_anim->GetBoundingBox(bx, by, &rect);
}
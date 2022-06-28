#include "Rocket.h"


Rocket::Rocket(float posx, float posy) : Bullet(posx, posy)
{
	rocket_anim = bulletResManger->GetAnimation("rocket_anim");
	rocket_anim->SetHotSpot(7.5, 0);
	rocket_anim->Play();
}


Rocket::~Rocket()
{
	delete bulletResManger;
	b_hge->Release();
}

void Rocket::render(float dt)
{
	rocket_anim->Update(dt);
	rocket_anim->Render(bx, by);
}

void Rocket::move()
{
	Bullet::move(Rocket::speed);
	rocket_anim->GetBoundingBox(bx, by, &rect);
}

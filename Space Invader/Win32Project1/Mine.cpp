#include "Mine.h"


Mine::Mine(float posx, float posy) : Bullet(posx, posy)
{
	mine_anim = bulletResManger->GetAnimation("mine_animt");
	mine_anim->SetHotSpot(16, 8);
	mine_anim->Play();
}


Mine::~Mine()
{
	delete bulletResManger;
	b_hge->Release();
}

void Mine::render(float dt)
{
	mine_anim->Update(dt);
	mine_anim->Render(bx, by);
}

void Mine::move()
{
	// mines don't move
	Bullet::move(Bullet::speed);
	mine_anim->GetBoundingBox(bx, by, &rect);
}

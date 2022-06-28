#include "Explosion.h"


Explosion::Explosion(float posx, float posy)
{
	e_hge = hgeCreate(HGE_VERSION);
	e_resManager = new hgeResourceManager("resources.res");
	explosionAnimation = e_resManager->GetAnimation("blue_explosion");
	
	ex = posx;
	ey = posy;
}


Explosion::~Explosion()
{
	delete e_resManager;
	e_hge->Release();
}

void Explosion::render()
{
	explosionAnimation->Render(ex, ey);
}

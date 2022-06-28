#include "Resource_Drop.h"
#include <time.h>


Resource_Drop::Resource_Drop(float posx, float posy)
{
	r_hge = hgeCreate(HGE_VERSION);
	r_resManager = new hgeResourceManager("resource.res");
	srand(static_cast<unsigned int> (time(NULL)));
	type = rand() % 4;	// from 0 to 3 

	if (type== 0)
		r_sprite = r_resManager->GetSprite("resource");
	else if (type== 1)
		r_sprite = r_resManager->GetSprite("ammo");
	else if (type== 2)
		r_sprite = r_resManager->GetSprite("armour");
	else if (type== 3)
		r_sprite = r_resManager->GetSprite("fuel");


	r_x = posx;
	r_y = posy;
}


Resource_Drop::~Resource_Drop()
{
	delete r_resManager;
	r_hge->Release();
}

void Resource_Drop::move()
{
	if (r_hge->Input_GetKeyState(HGEK_SHIFT))
		r_y += 5;
	else if (r_hge->Input_GetKeyState(HGEK_UP))
		r_y += 2.5;
	else
		r_y += 0.25;

	r_sprite->GetBoundingBox(r_x, r_y, &rect);
}

void Resource_Drop::render()
{
	r_sprite->Render(r_x, r_y);
}
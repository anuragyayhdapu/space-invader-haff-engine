#include "A11.h"


A11::A11(float posx, float posy)
{
	a11_hge = hgeCreate(HGE_VERSION);
	a_resManager = new hgeResourceManager("resource.res");

	normalAnim = a_resManager->GetAnimation("a11_normalAnim");
	bloffAnim = a_resManager->GetAnimation("a11_blastoffAnim");

	normalAnim->Play();
	bloffAnim->Play();

	x = posx, y = posy;
	blastoff = false;
}


A11::~A11()
{
	delete a_resManager;
	a11_hge->Release();
}

void A11::move()
{
	if (fuel > 0.0 && energy > 0.0)
	{
		if (a11_hge->Input_GetKeyState(HGEK_UP))
		{
			if (y > 470 - (470 / 2))
				y -= 5.0f;
			fuel -= 0.5;
		}
		if (a11_hge->Input_GetKeyState(HGEK_DOWN))
		{
			if (y < 380)
				y += 5.0f;	// problem with down, this value should be lower
		}
		if (a11_hge->Input_GetKeyState(HGEK_RIGHT))
		{
			if (x < 770)
				x += 5.0f;
		}
		if (a11_hge->Input_GetKeyState(HGEK_LEFT))
		{
			if (x > 10)
				x -= 5.0f;
		}
		
		// blastoff animation checks
		if (a11_hge->Input_KeyDown(HGEK_SHIFT) || a11_hge->Input_KeyDown(HGEK_UP))
			blastoff = true;
		if (a11_hge->Input_KeyUp(HGEK_SHIFT) || a11_hge->Input_KeyUp(HGEK_UP))
			blastoff = false;
	}

	// get the bounding box
	normalAnim->GetBoundingBox(x, y, &rect);
	bloffAnim->GetBoundingBox(x, y, &rect);
}

void A11::render(float dt)
{
	normalAnim->Update(dt);
	bloffAnim->Update(dt);

	if (blastoff)
		bloffAnim->Render(x, y);
	else if (!blastoff)
		normalAnim->Render(x, y);
}
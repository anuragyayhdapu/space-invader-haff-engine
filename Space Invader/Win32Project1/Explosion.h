#pragma once

#include <hge.h>
#include <hgeSprite.h>
#include <hgeresource.h>

class Explosion
{

protected:

	HGE					*e_hge;
	hgeResourceManager	*e_resManager;
	float				ex = 0.0f, ey = 0.0f;

public:

	hgeAnimation		*explosionAnimation;
	Explosion(float, float);
	~Explosion();

	void render();
};


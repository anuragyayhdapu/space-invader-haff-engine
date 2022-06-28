/*
	Properties that are different in each bullet :
	1. sprite					(done)
	2. collision area			(done)
	3. speed					(done)
	4. firing rate				
	5. damage					(done)
	6. animation - some bullets	(done)
*/

/*
	Properties that are same in every bullet:
	1. position x and y			(done)
	2. render and move forward	(done)
*/

/*
	No. of bullets :
	1. Machine gun bullets	(done)
	2. Rockets				(done)
	3. Space-mine			
	4. plasma_1				(done)
	5. plasma_2				(done)
	6. Fire ball			(done)
*/ 

#pragma once

#include <hge.h>
#include <hgeresource.h>
#include <hgesprite.h>

class Bullet
{
protected:
	HGE					*b_hge;
	hgeSprite			*bulletSprite;
	hgeResourceManager	*bulletResManger;
	float				bx;
	float				by;
	const float			speed = 5.0;
public:
	Bullet(float, float);
	~Bullet();
	void move(const float);
	void render(float, float);
	float getbullet_x() { return bx; }
	float getbullet_y() { return by; }
};


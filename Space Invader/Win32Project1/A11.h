#pragma once

#include <hge.h>
#include <hgeresource.h>
#include <hgesprite.h>


class A11
{
private:
	HGE					*a11_hge;
	hgeResourceManager	*a_resManager;
	hgeAnimation		*normalAnim;
	hgeAnimation		*bloffAnim;
	hgeRect				rect;

	float x, y;				// position x and y
	float fuel = 840.0f;
	float energy = 1000.0f;		// health
	
	int no_mc_bullets = 400;	// no. of machine bullets
	int no_plasma1 = 100;
	int no_plasma2 = 50;
	int no_firaball = 25;
	int no_rockets = 10;

	bool blastoff;

public:

	A11(float , float);
	~A11();

	void move();	// for movement and position
	void render(float dt);	// for rendering
	
	float	get_x() { return x; }
	float	get_y() { return y; }

	hgeRect getRect() { return rect; }
	float	getEnergy() { return energy; }
	float	getFuel() { return fuel; }

	void	setEnergy(float en) { energy = en; }
	void	setFuel(float f) { fuel = f; }		

	// bullet area
	int getMc_bullet() { return no_mc_bullets; }
	int getPlasma1() { return no_plasma1; }
	int getPlasma2() { return no_plasma2; }
	int getFireball() { return no_firaball; }
	int getRockets() { return no_rockets; }

	void setMc_bullet(int b) { no_mc_bullets = b; }
	void setPlasma1(int b) { no_plasma1 = b; }
	void setPlasma2(int b) { no_plasma2 = b; }
	void setFireball(int b) { no_firaball = b; }
	void setRockets(int b) { no_rockets = b; }

};


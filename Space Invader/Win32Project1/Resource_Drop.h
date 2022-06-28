#pragma once

#include <hge.h>
#include <hgeresource.h>
#include <hgesprite.h>

class Resource_Drop
{
private:
	HGE *r_hge;
	hgeSprite *r_sprite;
	hgeResourceManager *r_resManager;
	float r_x, r_y;
	hgeRect rect;
	int type = 0;

public:
	Resource_Drop(float, float);
	~Resource_Drop();

	void move();
	void render();

	float getr_x(){ return r_x; }
	float getr_y() { return r_y; }
	hgeRect getRect() { return rect; }
	int get_type() { return type; }
};


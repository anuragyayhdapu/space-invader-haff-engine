/*
	Don't forget
	1. Armour
	2. Smart Criterion for dropping resources
	3. Make background black	(done)
*/

/*	
	Next Target
	- Move a11 in a seperate class (done)
	- Implement Scoring	(done)
	- Menu 
*/

#include <Windows.h>
#include <hge.h>
#include <hgeresource.h>
#include <hgesprite.h>
#include <hgeanim.h>
#include <hgefont.h>
#include <time.h>
#include <vector>

#include "A11.h"
#include "Bullet.h"
#include "MachineBullet.h"
#include "PlasmaBullet_1.h"
#include "Rocket.h"
#include "Fireball.h"
#include "Mine.h"
#include "PlasmaBullet_2.h"
#include "Enemy.h"
#include "Enemy1.h"
#include "Enemy2.h"
#include "Enemy3.h"
#include "Resource_Drop.h"
#include "Scoring.h"

// Background Speeds
#define SPEED_1 1
#define SPEED_2 2
#define SPEED_3 10
#define SPEED_4 15

#define BULLET_SPEED 25

float bg_s = 0;					// speed for vertical scrolling background
float bg_x = 0;					// x position of background 1 
float bg_y = 0;					// y position of background 1
float bg_y2 = -470;				// y position if background 2
float a11_x = 405.0f;			// x position of a11
float a11_y = 380.0f;			// y position of a11
float ex_x = 0.0f, ex_y = 0.0f;	// explosion x and y

HGE					*hge = 0;

hgeFont				*font_fuel;				// font to display text
hgeFont				*font_ammo;
hgeFont				*font_health;
hgeFont				*font_score;

hgeSprite			*backgSprite1;		// object of sprite class, for background sprite
hgeSprite			*backgSprite2;		// 2nd background
hgeSprite			*bullet_1Sprite;	// sprite for bullet_1

hgeAnimation		*blueexplosion;		// animation for blue explosion
hgeAnimation		*rocketexplosion;	// animation for rocket explosion
hgeResourceManager	*resManager;		// object of resource manager

A11* a11;	// object of ship, a11

Scoring* scoring;	// for handling stats

std::vector<MachineBullet *>  v_mc_bullets;		// vector to hold machine bullets
std::vector<PlasmaBullet_1 *> v_pl1_bullets;	// vector to hold plasma 1 bullets
std::vector<PlasmaBullet_2 *> v_pl2_bullets;	// vector to hold plasma 2 bullets
std::vector<Rocket *>		  v_rockets;		// vector to hold rockets
std::vector<Fireball *>		  v_fireballs;		// vector to hold fireballs
std::vector<Mine *>			  v_mines;			// vector to hold mines

std::vector<Enemy1 *> v_enemy;	// vector to hold enemies1
std::vector<Enemy2 *> v_enemy2;	// vector to hold enemies2
std::vector<Enemy3 *> v_enemy3;	// vector to hold enemies3

std::vector<Resource_Drop*> v_resource;	// vector to hold resources

bool FrameFunc();
void Position_a11();					// manipulate position of a11(old) , now only checks for collision with enemy and moniters if health goes below zero
void Position_enemy();
void Background_move_speed(float);		// vertical scrolling of background
void Shoot_bullets(float);
void Create_explosion(float, float);	// creting explosion
void Explosion_render_update(float);
void Display_text();

void for_machine_gun_bullet();
void for_plasma1_bullets();
void for_rockets(float);
void for_fireballs(float);
void for_plasma2_bullets();
void for_space_mines(float);


bool buu	    = false;	// blue explosion
bool ruu		= false;	// rocket explosion

bool mc_bullet  = false;	// fire which type of bullet 
bool plasma_1   = false;
bool fireball   = false;
bool plasma_2   = false;
bool rocket	    = false;
bool mine	    = false;

bool wave1 = true;
bool wave2 = false;
bool wave3 = false;

int enemy_destroyed = 0;
void resource_drop();

// playing time calculation
time_t time1, time2;
double total_time = 0.0;


bool FrameFunc()	// The game loop code goes here
{
	float dt = hge->Timer_GetDelta();	// get the time since last frame

	if (bg_y >= 470)	// loop background 1
		bg_y = -470;
	if (bg_y2 >= 470)	// loop background 2
		bg_y2 = -470;

	hge->Gfx_BeginScene();
	hge->Gfx_Clear(0x000000);	// cleared the screen to black

	backgSprite1->Render(bg_x, bg_y + 235);	// background of background
	backgSprite2->Render(bg_x, bg_y2 + 235);
	backgSprite1->Render(bg_x, bg_y);	// render the backgroundSprite
	backgSprite2->Render(bg_x, bg_y2); // 2nd background

	Position_a11();
	Position_enemy();
	Shoot_bullets(dt);
	Background_move_speed(dt);	// also controls which animation for ship gets displayed
	Explosion_render_update(dt);
	Display_text();
	resource_drop();

	hge->Gfx_EndScene();

	if (hge->Input_GetKeyState(HGEK_ESCAPE))
	{
		scoring->WriteToFile();
		return true;
	}
	
	return false;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR nCmdLine, int nCmdShow)
{
	hge = hgeCreate(HGE_VERSION);
	
	// Set up log file, frame function, render function and window title
	hge->System_SetState(HGE_LOGFILE, "Space Invader.log");
	hge->System_SetState(HGE_FRAMEFUNC, FrameFunc);
	hge->System_SetState(HGE_TITLE, "Space Invader 2D");

	// set video mode
	hge->System_SetState(HGE_FPS, 60);
	hge->System_SetState(HGE_WINDOWED, true);
	hge->System_SetState(HGE_SCREENWIDTH, 810);
	hge->System_SetState(HGE_SCREENHEIGHT, 470);
	hge->System_SetState(HGE_USESOUND, true);	// when enabled game crashes, make sure to place bass.dll

	if (hge->System_Initiate())	// System_Initiate, Initializes all hardware and software needed to run the engine
								// and creates the application window
	{
		// Resource manager defines textures, sprites and sounds
		resManager = new hgeResourceManager("resource.res");
		backgSprite1 = resManager->GetSprite("backgroundSprite1");
		backgSprite2 = resManager->GetSprite("backgroundSprite2");

		blueexplosion = resManager->GetAnimation("blue_explosion");
		blueexplosion->SetHotSpot(45, 45);
		rocketexplosion = resManager->GetAnimation("rocket_explosion");
		rocketexplosion->SetHotSpot(31, 29);

		font_fuel = resManager->GetFont("font");
		font_fuel->SetColor(ARGB(255, 0, 139, 190));
		font_fuel->SetScale(2.0);
		font_ammo = resManager->GetFont("font");
		font_ammo->SetColor(ARGB(255, 0, 139, 190));
		font_health = resManager->GetFont("font");
		font_health->SetColor(ARGB(255, 0, 139, 190));
		font_score = resManager->GetFont("font");
		font_score->SetColor(ARGB(255, 0, 139, 190));
		
		blueexplosion->Play();
		rocketexplosion->Play();

		// Should be the best place to Initiate a11, (if adding menu, then not here)
		a11 = new A11(a11_x, a11_y);
		time(&time1);	// start the time
		scoring = new Scoring();

		// Start the system
		hge->System_Start();
	}
	
	else
		MessageBox(NULL, hge->System_GetErrorMessage(), "Error", MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);

	// Cleanup and shut down
	/*delete backgSprite1;
	delete backgSprite2;
	delete a11nAnim;
	delete a11bloffAnim;
	delete bullet_1Sprite;*/

	delete resManager;
	hge->System_Shutdown();
	hge->Release();

	return 0;
}

void Background_move_speed(float dt)
{
	if (a11->getFuel() > 0.0)
	{
		if (a11->getEnergy() >= 0.0)
		{
			if (hge->Input_GetKeyState(HGEK_DOWN))
			{
				if (bg_s > SPEED_1)
					bg_s = bg_s - 0.10f;
				a11->render(dt);
				a11->move();
			}
			else if (hge->Input_GetKeyState(HGEK_UP))
			{
				if (bg_s < SPEED_3)
					bg_s = bg_s + 0.20f;
				a11->render(dt);
				a11->move();
			}

			else if (hge->Input_GetKeyState(HGEK_SHIFT) && a11->getFuel() > 50.0)
			{
				bg_s = SPEED_4;
				a11->setFuel(a11->getFuel() - 10.0f);
				a11->render(dt);
				a11->move();
			}
			else if (!(hge->Input_GetKeyState(HGEK_UP)))
			{
				if (bg_s > SPEED_2)
					bg_s = bg_s - 0.10f;
				else
					bg_s = SPEED_2;
				a11->render(dt);
				a11->move();
			}
		}
	}
	
	
	bg_y += bg_s;
	bg_y2 += bg_s;
}

void Position_a11()
{
	/*if (a11_fuel > 0.0 && a11_health > 0.0)
	{
		if (hge->Input_GetKeyState(HGEK_UP))	// Up
		{
			if (a11_fuel >= 0.0)
			{
				if (a11_y > 470 - (470 / 2))
					a11_y -= 5.0f;
				a11_fuel -= 0.5;
			}
		}
		if (hge->Input_GetKeyState(HGEK_DOWN))	// Down
		{
			if (a11_y < 380)
				a11_y += 5.0f;
		}
		if (hge->Input_GetKeyState(HGEK_RIGHT))	// Right
		{
			if (a11_x < 770)
				a11_x += 5.0f;
		}
		if (hge->Input_GetKeyState(HGEK_LEFT))	// Left
		{
			if (a11_x > 10)
				a11_x -= 5.0f;
		}
	}*/

	// a11 collision check with enemy
	for (unsigned int i = 0; i < v_enemy.size(); i++)
	{
		Enemy1 *p_enemy = v_enemy.at(i);
		if (a11->getRect().Intersect(&p_enemy->getRect()))
		{
			buu = true;
			ex_x = a11->get_x();
			ex_y = a11->get_y();
			a11->setEnergy(a11->getEnergy() - p_enemy->getDamage());
		}
	}
	for (unsigned int i = 0; i < v_enemy2.size(); i++)
	{
		Enemy2 *p_enemy = v_enemy2.at(i);
		if (a11->getRect().Intersect(&p_enemy->getRect()))
		{
			buu = true;
			ex_x = a11->get_x();
			ex_y = a11->get_y();
			a11->setEnergy(a11->getEnergy() - p_enemy->getDamage());
		}
	}
	for (unsigned int i = 0; i < v_enemy3.size(); i++)
	{
		Enemy3 *p_enemy = v_enemy3.at(i);
		if (a11->getRect().Intersect(&p_enemy->getRect()))
		{
			ruu = true;
			ex_x = a11->get_x();
			ex_y = a11->get_y();
			a11->setEnergy(a11->getEnergy() - p_enemy->getDamage());
		}
	}

	if (a11->getEnergy() <= 0.0)
	{
		ruu = true;
		ex_x = a11->get_x() + 17;
		ex_y = a11->get_y() + 40;
	}

}

void Shoot_bullets(float dt) 
{
	
	if (hge->Input_KeyDown(HGEK_1))
	{
		mc_bullet = true; 
		plasma_1 = fireball = plasma_2 = rocket = mine = false;
	}
	else if (hge->Input_KeyDown(HGEK_2))
	{
		plasma_1 = true;
		mc_bullet = fireball = plasma_2 = rocket = mine = false;
	}
	else if (hge->Input_KeyDown(HGEK_3))
	{
		plasma_2 = true;
		mc_bullet = fireball = plasma_1 = rocket = mine = false;
	}
	else if (hge->Input_KeyDown(HGEK_4))
	{
		fireball = true;
		mc_bullet = plasma_2 = plasma_1 = rocket = mine = false;
	}
	else if (hge->Input_KeyDown(HGEK_5))
	{
		rocket = true;
		mc_bullet = plasma_2 = plasma_1 = fireball = mine = false;
	}
	else if (hge->Input_KeyDown(HGEK_6))
	{
		mine = true;
		mc_bullet = plasma_2 = plasma_1 = rocket = fireball = false;
	}

	if (hge->Input_KeyDown(HGEK_SPACE) && (a11->getEnergy() > 0.0 && a11->getFuel() > 0.0))
	{
		if (mc_bullet && a11->getMc_bullet() > 0)
		{
			v_mc_bullets.push_back(new MachineBullet(a11->get_x(), a11->get_y()));
			a11->setMc_bullet(a11->getMc_bullet() - 2);
		}
		else if (plasma_1 && a11->getPlasma1() > 0)
		{
			v_pl1_bullets.push_back(new PlasmaBullet_1(a11->get_x(), a11->get_y()));
			a11->setPlasma1(a11->getPlasma1() - 1);
		}
		else if (plasma_2 && a11->getPlasma2() > 0)
		{
			v_pl2_bullets.push_back(new PlasmaBullet_2(a11->get_x(), a11->get_y()));
			a11->setPlasma2(a11->getPlasma2() - 1);
		}
		else if (fireball && a11->getFireball() > 0)
		{
			v_fireballs.push_back(new Fireball(a11->get_x(), a11->get_y()));
			a11->setFireball(a11->getFireball() - 1);
		}
		else if (rocket && a11->getRockets() > 0)
		{
			v_rockets.push_back(new Rocket(a11->get_x(), a11->get_y()));
			a11->setRockets(a11->getRockets() - 1);
		}
		
	}

	for_machine_gun_bullet();

	for_plasma1_bullets();

	for_plasma2_bullets();
	
	for_rockets(dt);
	
	for_fireballs(dt);

	for_plasma2_bullets();
}

void Explosion_render_update(float dt)
{
	if (a11->getFuel() <= 0.0 || a11->getEnergy() <= 0.0)	// i.e a11 khatam
	{
		ex_x = a11->get_x();
		ex_y = a11->get_y();
		buu = true;
		ruu = true;

		// write every score to the file
		scoring->WriteToFile();
	}

	if (buu == true)
	{
		if (blueexplosion->GetFrame() == 10)
		{
			buu = false;
			blueexplosion->SetFrame(0);
		}
		else
		{
			blueexplosion->Update(dt);
			blueexplosion->Render(ex_x, ex_y);
		}
	}
	if (ruu == true)
	{
		if (rocketexplosion->GetFrame() == 24)
		{
			ruu = false;
			rocketexplosion->SetFrame(0);
		}
		else
		{
			rocketexplosion->Update(dt);
			rocketexplosion->Render(ex_x, ex_y);
		}
	}
}

void for_machine_gun_bullet()
{
	if (mc_bullet)
	{
		for (unsigned int i = 0; i < v_mc_bullets.size(); i++)
		{
			MachineBullet *p_bullet = v_mc_bullets.at(i);
			p_bullet->move();
			p_bullet->render();
		}
		for (unsigned int i = 0; i < v_mc_bullets.size(); i++)
		{
			MachineBullet *p_bullet = v_mc_bullets.at(i);
			if (p_bullet->getbullet_y() <= 10)
			{
				delete p_bullet;
				v_mc_bullets.erase(v_mc_bullets.begin() + i);
			}
		}
		// Collision check
		//enemy 1
		for (unsigned int i = 0; i < v_mc_bullets.size(); i++)
		{
			MachineBullet *p_bullet = v_mc_bullets.at(i);
			for (unsigned int j = 0; j < v_enemy.size(); j++)
			{
				Enemy1 *p_enemy = v_enemy.at(j);
				if (p_bullet->getRect().Intersect(&p_enemy->getRect()) || p_bullet->getRect2().Intersect(&p_enemy->getRect()))
				{
					buu = true;
					ex_x = p_bullet->getbullet_x();
					ex_y = p_bullet->getbullet_y();

					p_enemy->setHealth(p_enemy->getHealth() - p_bullet->getDamage());
					if (p_enemy->getHealth() <= 0.0)
					{
						enemy_destroyed++;
						scoring->setScore(scoring->getScore() + 10);
						delete p_enemy;
						v_enemy.erase(v_enemy.begin() + j);
					}

					delete p_bullet;
					v_mc_bullets.erase(v_mc_bullets.begin() + i);
				}
			}
			// enemy 2
			for (unsigned int j = 0; j < v_enemy2.size(); j++)
			{
				Enemy2 *p_enemy = v_enemy2.at(j);
				if (p_bullet->getRect().Intersect(&p_enemy->getRect()) || p_bullet->getRect2().Intersect(&p_enemy->getRect()))
				{
					buu = true;
					ex_x = p_bullet->getbullet_x();
					ex_y = p_bullet->getbullet_y();

					p_enemy->setHealth(p_enemy->getHealth() - p_bullet->getDamage());
					if (p_enemy->getHealth() <= 0.0)
					{
						enemy_destroyed++;
						scoring->setScore(scoring->getScore() + 25);
						delete p_enemy;
						v_enemy2.erase(v_enemy2.begin() + j);
					}

					delete p_bullet;
					v_mc_bullets.erase(v_mc_bullets.begin() + i);
				}
			}
			// enemy 3
			for (unsigned int j = 0; j < v_enemy3.size(); j++)
			{
				Enemy3 *p_enemy = v_enemy3.at(j);
				if (p_bullet->getRect().Intersect(&p_enemy->getRect()) || p_bullet->getRect2().Intersect(&p_enemy->getRect()))
				{
					buu = true;
					ex_x = p_bullet->getbullet_x();
					ex_y = p_bullet->getbullet_y();

					p_enemy->setHealth(p_enemy->getHealth() - p_bullet->getDamage());
					if (p_enemy->getHealth() <= 0.0)
					{
						enemy_destroyed++;
						scoring->setScore(scoring->getScore() + 50);
						ruu = true;
						ex_x = p_enemy->getenemy_x();
						ex_y = p_enemy->getenemy_y();
						delete p_enemy;
						v_enemy3.erase(v_enemy3.begin() + j);
					}

					delete p_bullet;
					v_mc_bullets.erase(v_mc_bullets.begin() + i);
				}
			}
		}
	}
}

void for_plasma1_bullets()
{
	if (plasma_1)
	{
		for (unsigned int i = 0; i < v_pl1_bullets.size(); i++)
		{
			PlasmaBullet_1 *p_bullet = v_pl1_bullets.at(i);
			p_bullet->move();
			p_bullet->render();
		}
		for (unsigned int i = 0; i < v_pl1_bullets.size(); i++)
		{
			PlasmaBullet_1 *p_bullet = v_pl1_bullets.at(i);
			if (p_bullet->getbullet_y() <= 10)
			{
				delete p_bullet;
				v_pl1_bullets.erase(v_pl1_bullets.begin() + i);
			}
		}
		// Collision check
		// enemy 1
		for (unsigned int i = 0; i < v_pl1_bullets.size(); i++)
		{
			PlasmaBullet_1 *p_bullet = v_pl1_bullets.at(i);
			for (unsigned int j = 0; j < v_enemy.size(); j++)
			{
				Enemy1 *p_enemy = v_enemy.at(j);
				if (p_bullet->getRect().Intersect(&p_enemy->getRect()))
				{
					buu = true;
					ex_x = p_bullet->getbullet_x();
					ex_y = p_bullet->getbullet_y();

					p_enemy->setHealth(p_enemy->getHealth() - p_bullet->getDamage());
					if (p_enemy->getHealth() <= 0.0)
					{
						enemy_destroyed++;
						scoring->setScore(scoring->getScore() + 10);
						delete p_enemy;
						v_enemy.erase(v_enemy.begin() + j);
					}

					delete p_bullet;
					v_pl1_bullets.erase(v_pl1_bullets.begin() + i);
				}
			}
			// enemy 2
			for (unsigned int j = 0; j < v_enemy2.size(); j++)
			{
				Enemy2 *p_enemy = v_enemy2.at(j);
				if (p_bullet->getRect().Intersect(&p_enemy->getRect()))
				{
					buu = true;
					ex_x = p_bullet->getbullet_x();
					ex_y = p_bullet->getbullet_y();

					p_enemy->setHealth(p_enemy->getHealth() - p_bullet->getDamage());
					if (p_enemy->getHealth() <= 0.0)
					{
						enemy_destroyed++;
						scoring->setScore(scoring->getScore() + 25);
						delete p_enemy;
						v_enemy2.erase(v_enemy2.begin() + j);
					}

					delete p_bullet;
					v_pl1_bullets.erase(v_pl1_bullets.begin() + i);
				}
			}
			// enemy 3
			for (unsigned int j = 0; j < v_enemy3.size(); j++)
			{
				Enemy3 *p_enemy = v_enemy3.at(j);
				if (p_bullet->getRect().Intersect(&p_enemy->getRect()))
				{
					buu = true;
					ex_x = p_bullet->getbullet_x();
					ex_y = p_bullet->getbullet_y();

					p_enemy->setHealth(p_enemy->getHealth() - p_bullet->getDamage());
					if (p_enemy->getHealth() <= 0.0)
					{
						enemy_destroyed++;
						scoring->setScore(scoring->getScore() + 50);
						ruu = true;
						ex_x = p_enemy->getenemy_x();
						ex_y = p_enemy->getenemy_y();
						delete p_enemy;
						v_enemy3.erase(v_enemy3.begin() + j);
					}

					delete p_bullet;
					v_pl1_bullets.erase(v_pl1_bullets.begin() + i);
				}
			}
		}
	}
}

void for_rockets(float dt)
{
	if (rocket)
	{
		for (unsigned int i = 0; i < v_rockets.size(); i++)
		{
			Rocket *p_bullet = v_rockets.at(i);
			p_bullet->move();
			p_bullet->render(dt);
		}
		for (unsigned int i = 0; i < v_rockets.size(); i++)
		{
			Rocket *p_bullet = v_rockets.at(i);
			if (p_bullet->getbullet_y() <= 10)
			{
				delete p_bullet;
				v_rockets.erase(v_rockets.begin() + i);
			}
		}
		// Collision check
		// enemy 1
		for (unsigned int i = 0; i < v_rockets.size(); i++)
		{
			Rocket *p_bullet = v_rockets.at(i);
			for (unsigned int j = 0; j < v_enemy.size(); j++)
			{
				Enemy1 *p_enemy = v_enemy.at(j);
				if (p_bullet->getRect().Intersect(&p_enemy->getRect()))
				{
					ruu = true;
					ex_x = p_bullet->getbullet_x();
					ex_y = p_bullet->getbullet_y();

					p_enemy->setHealth(p_enemy->getHealth() - p_bullet->getDamage());
					if (p_enemy->getHealth() <= 0.0)
					{
						enemy_destroyed++;
						scoring->setScore(scoring->getScore() + 20);
						delete p_enemy;
						v_enemy.erase(v_enemy.begin() + j);
					}

					delete p_bullet;
					v_rockets.erase(v_rockets.begin() + i);
				}
			}
			// enemy 2
			for (unsigned int j = 0; j < v_enemy2.size(); j++)
			{
				Enemy2 *p_enemy = v_enemy2.at(j);
				if (p_bullet->getRect().Intersect(&p_enemy->getRect()))
				{
					ruu = true;
					ex_x = p_bullet->getbullet_x();
					ex_y = p_bullet->getbullet_y();

					p_enemy->setHealth(p_enemy->getHealth() - p_bullet->getDamage());
					if (p_enemy->getHealth() <= 0.0)
					{
						enemy_destroyed++;
						scoring->setScore(scoring->getScore() + 35);
						delete p_enemy;
						v_enemy2.erase(v_enemy2.begin() + j);
					}

					delete p_bullet;
					v_rockets.erase(v_rockets.begin() + i);
				}
			}
			// enemy 3
			for (unsigned int j = 0; j < v_enemy3.size(); j++)
			{
				Enemy3 *p_enemy = v_enemy3.at(j);
				if (p_bullet->getRect().Intersect(&p_enemy->getRect()))
				{
					ruu = true;
					ex_x = p_bullet->getbullet_x();
					ex_y = p_bullet->getbullet_y();

					p_enemy->setHealth(p_enemy->getHealth() - p_bullet->getDamage());
					if (p_enemy->getHealth() <= 0.0)
					{
						enemy_destroyed++;
						scoring->setScore(scoring->getScore() + 60);
						ruu = true;
						ex_x = p_enemy->getenemy_x();
						ex_y = p_enemy->getenemy_y();
						delete p_enemy;
						v_enemy3.erase(v_enemy3.begin() + j);
					}

					delete p_bullet;
					v_rockets.erase(v_rockets.begin() + i);
				}
			}
		}
	}
}

void for_fireballs(float dt)
{
	if (fireball)
	{
		for (unsigned int i = 0; i < v_fireballs.size(); i++)
		{
			Fireball *p_bullet = v_fireballs.at(i);
			p_bullet->move();
			p_bullet->render(dt);
		}
		for (unsigned int i = 0; i < v_fireballs.size(); i++)
		{
			Fireball *p_bullet = v_fireballs.at(i);
			if (p_bullet->getbullet_y() <= 10)
			{
				delete p_bullet;
				v_fireballs.erase(v_fireballs.begin() + i);
			}
		}
		// Collision check
		// enemy 1
		for (unsigned int i = 0; i < v_fireballs.size(); i++)
		{
			Fireball *p_bullet = v_fireballs.at(i);
			for (unsigned int j = 0; j < v_enemy.size(); j++)
			{
				Enemy1 *p_enemy = v_enemy.at(j);
				if (p_bullet->getRect().Intersect(&p_enemy->getRect()))
				{
					ruu = true;
					ex_x = p_bullet->getbullet_x();
					ex_y = p_bullet->getbullet_y();

					p_enemy->setHealth(p_enemy->getHealth() - p_bullet->getDamage());
					if (p_enemy->getHealth() <= 0.0)
					{
						enemy_destroyed++;
						scoring->setScore(scoring->getScore() + 15);
						delete p_enemy;
						v_enemy.erase(v_enemy.begin() + j);
					}

					delete p_bullet;
					v_fireballs.erase(v_fireballs.begin() + i);
				}
			}
			// enemy 2
			for (unsigned int j = 0; j < v_enemy2.size(); j++)
			{
				Enemy2 *p_enemy = v_enemy2.at(j);
				if (p_bullet->getRect().Intersect(&p_enemy->getRect()))
				{
					ruu = true;
					ex_x = p_bullet->getbullet_x();
					ex_y = p_bullet->getbullet_y();

					p_enemy->setHealth(p_enemy->getHealth() - p_bullet->getDamage());
					if (p_enemy->getHealth() <= 0.0)
					{
						enemy_destroyed++;
						scoring->setScore(scoring->getScore() + 30);
						delete p_enemy;
						v_enemy2.erase(v_enemy2.begin() + j);
					}

					delete p_bullet;
					v_fireballs.erase(v_fireballs.begin() + i);
				}
			}
			// enemy 3
			for (unsigned int j = 0; j < v_enemy3.size(); j++)
			{
				Enemy3 *p_enemy = v_enemy3.at(j);
				if (p_bullet->getRect().Intersect(&p_enemy->getRect()))
				{
					ruu = true;
					ex_x = p_bullet->getbullet_x();
					ex_y = p_bullet->getbullet_y();

					p_enemy->setHealth(p_enemy->getHealth() - p_bullet->getDamage());
					if (p_enemy->getHealth() <= 0.0)
					{
						enemy_destroyed++;
						scoring->setScore(scoring->getScore() + 55);
						ruu = true;
						ex_x = p_enemy->getenemy_x();
						ex_y = p_enemy->getenemy_y();
						delete p_enemy;
						v_enemy3.erase(v_enemy3.begin() + j);
					}

					delete p_bullet;
					v_fireballs.erase(v_fireballs.begin() + i);
				}
			}
		}
	}
}

void for_plasma2_bullets()
{
	if (plasma_2)
	{
		for (unsigned int i = 0; i < v_pl2_bullets.size(); i++)
		{
			PlasmaBullet_2 *p_bullet = v_pl2_bullets.at(i);
			p_bullet->move();
			p_bullet->render();
		}
		for (unsigned int i = 0; i < v_pl2_bullets.size(); i++)
		{
			PlasmaBullet_2 *p_bullet = v_pl2_bullets.at(i);
			if (p_bullet->getbullet_y() <= 10)
			{
				delete p_bullet;
				v_pl2_bullets.erase(v_pl2_bullets.begin() + i);
			}
		}
		// Collision check
		// enemy 1
		for (unsigned int i = 0; i < v_pl2_bullets.size(); i++)
		{
			PlasmaBullet_2 *p_bullet = v_pl2_bullets.at(i);
			for (unsigned int j = 0; j < v_enemy.size(); j++)
			{
				Enemy1 *p_enemy = v_enemy.at(j);
				if (p_bullet->getRect().Intersect(&p_enemy->getRect()))
				{
					buu = true;
					ex_x = p_bullet->getbullet_x();
					ex_y = p_bullet->getbullet_y();

					p_enemy->setHealth(p_enemy->getHealth() - p_bullet->getDamage());
					if (p_enemy->getHealth() <= 0.0)
					{
						enemy_destroyed++;
						scoring->setScore(scoring->getScore() + 10);
						delete p_enemy;
						v_enemy.erase(v_enemy.begin() + j);
					}

					delete p_bullet;
					v_pl2_bullets.erase(v_pl2_bullets.begin() + i);
				}
			}
			// enemy 2
			for (unsigned int j = 0; j < v_enemy2.size(); j++)
			{
				Enemy2 *p_enemy = v_enemy2.at(j);
				if (p_bullet->getRect().Intersect(&p_enemy->getRect()))
				{
					buu = true;
					ex_x = p_bullet->getbullet_x();
					ex_y = p_bullet->getbullet_y();

					p_enemy->setHealth(p_enemy->getHealth() - p_bullet->getDamage());
					if (p_enemy->getHealth() <= 0.0)
					{
						enemy_destroyed++;
						scoring->setScore(scoring->getScore() + 25);
						delete p_enemy;
						v_enemy2.erase(v_enemy2.begin() + j);
					}

					delete p_bullet;
					v_pl2_bullets.erase(v_pl2_bullets.begin() + i);
				}
			}
			// enemy 3
			for (unsigned int j = 0; j < v_enemy3.size(); j++)
			{
				Enemy3 *p_enemy = v_enemy3.at(j);
				if (p_bullet->getRect().Intersect(&p_enemy->getRect()))
				{
					buu = true;
					ex_x = p_bullet->getbullet_x();
					ex_y = p_bullet->getbullet_y();

					p_enemy->setHealth(p_enemy->getHealth() - p_bullet->getDamage());
					if (p_enemy->getHealth() <= 0.0)
					{
						enemy_destroyed++;
						scoring->setScore(scoring->getScore() + 50);
						ruu = true;
						ex_x = p_enemy->getenemy_x();
						ex_y = p_enemy->getenemy_y();
						delete p_enemy;
						v_enemy3.erase(v_enemy3.begin() + j);
					}

					delete p_bullet;
					v_pl2_bullets.erase(v_pl2_bullets.begin() + i);
				}
			}
		}
	}
}

void Position_enemy()
{
	if (wave1)
	{
		if (v_enemy.size() < 2)
		{
			for (float i = 200; i < 700; i += 100)
			{
				v_enemy.push_back(new Enemy1(i, -20, a11->getFuel()));
				v_enemy.push_back(new Enemy1(i, -50, a11->getFuel()));
				v_enemy.push_back(new Enemy1(i, -80, a11->getFuel()));
				v_enemy.push_back(new Enemy1(i, -110, a11->getFuel()));
				v_enemy.push_back(new Enemy1(i, -140, a11->getFuel()));
				v_enemy.push_back(new Enemy1(i, -170, a11->getFuel()));
				v_enemy.push_back(new Enemy1(i, -200, a11->getFuel()));
			}
		}
		wave1 = false;
	}
	if (wave1 == false && v_enemy.size() == 0) { wave2 = true; }

	if (wave2)
	{
		if (v_enemy2.size() == 0) { wave2 = false; }
		if (v_enemy2.size() < 1)
		{
			for (float i = 200; i < 700; i += 100)
			{
				v_enemy2.push_back(new Enemy2(i, -20, a11->getFuel()));
				v_enemy2.push_back(new Enemy2(i, -60, a11->getFuel()));
			}
		}
	}
	if (wave2 == false && v_enemy.size() == 0) { wave3 = true; }

	if (wave3)
	{
		if (v_enemy3.size() < 2)
		{
			for (float i = 200; i < 700; i += 100)
			{
				v_enemy3.push_back(new Enemy3(i, -20, a11->getFuel()));
			}
		}
		wave3 = false;
	}
	
	// enemy 1
	for (unsigned int i = 0; i < v_enemy.size(); i++)
	{
		Enemy1 *p_enemy = v_enemy.at(i);
		p_enemy->render();
		p_enemy->move(a11->getFuel());
	}
	for (unsigned int i = 0; i < v_enemy.size(); i++)
	{
		Enemy1 *p_enemy = v_enemy.at(i);
		if (p_enemy->getenemy_y() >= 500)
		{
			delete p_enemy;
			v_enemy.erase(v_enemy.begin() + i);
		}
	}
	// enemy 2
	for (unsigned int i = 0; i < v_enemy2.size(); i++)
	{
		Enemy2 *p_enemy = v_enemy2.at(i);
		p_enemy->render();
		p_enemy->move(a11->getFuel());
	}
	for (unsigned int i = 0; i < v_enemy2.size(); i++)
	{
		Enemy2 *p_enemy = v_enemy2.at(i);
		if (p_enemy->getenemy_y() >= 550)
		{
			delete p_enemy;
			v_enemy2.erase(v_enemy2.begin() + i);
		}
	}
	// enemy 3
	for (unsigned int i = 0; i < v_enemy3.size(); i++)
	{
		Enemy3 *p_enemy = v_enemy3.at(i);
		p_enemy->render();
		p_enemy->move(a11->getFuel());
	}
	for (unsigned int i = 0; i < v_enemy3.size(); i++)
	{
		Enemy3 *p_enemy = v_enemy3.at(i);
		if (p_enemy->getenemy_y() >= 600)
		{
			delete p_enemy;
			v_enemy3.erase(v_enemy3.begin() + i);
		}
	}
}

void Display_text()
{
	//at the end of game, display different score
	if (a11->getFuel() <= 0.0 || a11->getEnergy() <= 0.0)
	{
		if (total_time == 0.0)
		{
			time(&time2);	// stop time
			total_time = difftime(time2, time1);
			scoring->setTotalTime(total_time);
		}

		font_score->printf(5, 100, HGETEXT_LEFT, "Highscore %d", scoring->getHighScore());
		font_score->printf(5, 120, HGETEXT_LEFT, "Your score %d", scoring->getScore());
		//font_score->printf(5, 140, HGETEXT_LEFT, "Total Distance %d", scoring->getDistanceTraveld());
		font_score->printf(5, 140, HGETEXT_LEFT, "Total Time %.1f s", scoring->getTotalTime());
	}

	else // if a11 alive
	{
		font_fuel->printf(5, 395, HGETEXT_LEFT, "Fuel %.1f", a11->getFuel());

		if (mc_bullet)
			font_ammo->printf(5, 415, HGETEXT_LEFT, "Ammo %d", a11->getMc_bullet());
		else if (plasma_1)
			font_ammo->printf(5, 415, HGETEXT_LEFT, "Ammo %d", a11->getPlasma1());
		else if (plasma_2)
			font_ammo->printf(5, 415, HGETEXT_LEFT, "Ammo %d", a11->getPlasma2());
		else if (fireball)
			font_ammo->printf(5, 415, HGETEXT_LEFT, "Ammo %d", a11->getFireball());
		else if (rocket)
			font_ammo->printf(5, 415, HGETEXT_LEFT, "Ammo %d", a11->getRockets());
		else
			font_ammo->printf(5, 415, HGETEXT_LEFT, "Num 1-5 Ammo");

		font_health->printf(5, 435, HGETEXT_LEFT, "Energy %.1f", a11->getEnergy());

		font_score->printf(5, 370, HGETEXT_LEFT, "Score %d", scoring->getScore());

		if (a11->getFuel() <= 50.0)
		{
			font_fuel->printf(700, 435, HGETEXT_LEFT, "Low Fuel");
		}
	}
}

void resource_drop()
{
	if (enemy_destroyed >= 4)
	{
		// Dropping the resource
		srand(static_cast <unsigned int> (time(NULL)));
		int drop_x = 25 + rand() % 785;

		v_resource.push_back(new Resource_Drop(drop_x, 0));
		enemy_destroyed = 0;	// reset enemy destroyed
	}
	
	for (unsigned int i = 0; i < v_resource.size(); i++)
	{
		Resource_Drop *p_resDrop = v_resource.at(i);
		p_resDrop->move();
		p_resDrop->render();
		if (a11->getRect().Intersect(&p_resDrop->getRect()))
		{

			// resources
			if (p_resDrop->get_type() == 0)	
			{
				a11->setPlasma1(a11->getPlasma1() + 25);	// smaller guns dosen't matter
				a11->setPlasma2(a11->getPlasma2() + 12);
				a11->setMc_bullet(a11->getMc_bullet() + 100);

				if (a11->getFireball() <= 19)
					a11->setFireball(a11->getFireball() + 6);
				else
					a11->setFireball(25);

				if (a11->getRockets() <= 8)
					a11->setRockets(a11->getRockets() + 2);
				else
					a11->setRockets(10);

				if (a11->getFuel() <= 600)
					a11->setFuel(a11->getFuel() + 200.0f);
				else
					a11->setFuel(840);

				if (a11->getEnergy() <= 750.0f)
					a11->setEnergy(a11->getEnergy() + 250.0f);
				else
					a11->setEnergy(1000.0f);
			}

			// ammo
			else if (p_resDrop->get_type() == 1)	
			{
				a11->setPlasma1(a11->getPlasma1() + 50);	// smaller guns dosen't matter
				a11->setPlasma2(a11->getPlasma2() + 25);
				a11->setMc_bullet(a11->getMc_bullet() + 200);

				if (a11->getFireball() <= 25)
					a11->setFireball(a11->getFireball() + 12);
				else
					a11->setFireball(25);

				if (a11->getRockets() <= 5)
					a11->setRockets(a11->getRockets() + 5);
				else
					a11->setRockets(10);
			}

			// armour
			else if (p_resDrop->get_type() == 2)	
			{
				// code for armour goes here
				// probably give extra health, and call it armour
			}

			// fuel
			else if (p_resDrop->get_type() == 3)
			{
				if (a11->getFuel() <= 420.0f)
					a11->setFuel(a11->getFuel() + 420.0f);
				else
					a11->setFuel(840.0f);
			}

		}

		// Removing the resource
		if (p_resDrop->getr_y() > 470 || a11->getRect().Intersect(&p_resDrop->getRect()))	// if out of area or collided with a11
		{
			delete p_resDrop;
			v_resource.erase(v_resource.begin() + i);
		}
	}
}
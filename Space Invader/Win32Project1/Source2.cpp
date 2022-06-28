/*#include <Windows.h>
#include <hge.h>

HGE *hge = 0;
hgeQuad quad;	// for rendering graphics
HEFFECT sound;	// for sound effects

// gameplay variables
float x = 100.0f, y = 100.0f;
float dx = 0.0f, dy = 0.0f;
const float speed = 90;
const float friction = 0.98f;

bool FrameFunc();
bool RenderFunc();
void boom();

void boom()	// to play collision sound with parameters based on sprite position and speed
{
	int pan = int((x - 400) / 4);
	float pitch = (dx * dx + dy * dy)*0.0005f + 0.2f;
	hge->Effect_PlayEx(sound, 100, pan, pitch);
}

bool FrameFunc()
{
	float dt = hge->Timer_GetDelta();

	if (hge->Input_GetKeyState(HGEK_ESCAPE))
		return true;
	if (hge->Input_GetKeyState(HGEK_LEFT))
		dx -= speed*dt;
	if (hge->Input_GetKeyState(HGEK_RIGHT))
		dx += speed*dt;
	if (hge->Input_GetKeyState(HGEK_UP))
		dy -= speed*dt;
	if (hge->Input_GetKeyState(HGEK_DOWN))
		dy += speed*dt;

	// Do some movment calculation and collision detection, specific to this game
	dx *= friction;
	dy *= friction;
	x += dx;
	y += dy;
	if (x > 784)
	{
		x = 784 - (x - 784);
		dx -= dx;
		boom();
	}
	if (x < 16)
	{
		x = 16 + 16 - x;
		dx = -dx;
		boom();
	}
	if (x > 584)
	{
		y = 584 - (y - 584);
		dy = -dy;
		boom();
	}
	if (y < 16)
	{
		y = 16 + 16;
		dy = -dy;
		boom();
	}

	// Update the quad's vertices to reflect the changes
	quad.v[0].x = x - 16; quad.v[0].y = y - 16;
	quad.v[1].x = x + 16; quad.v[1].y = y - 16;
	quad.v[2].x = x + 16; quad.v[2].y = y + 16;
	quad.v[3].x = x - 16; quad.v[3].y = y + 16;

	/*if (hge->Input_GetKeyState(HGEK_ESCAPE))
	return true;

	// return false to continue execution
	return false;
}

// The rendering function
bool RenderFunc()
{
	hge->Gfx_BeginScene();
	hge->Gfx_Clear(0);
	hge->Gfx_RenderQuad(&quad);
	hge->Gfx_EndScene();

	// rendering functin should alwys return false
	return false;
}


int WINAPI Custom_WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR nCmdLine, int nCmdShow)
{
	hge = hgeCreate(HGE_VERSION);

	// Set up log file, frame function, render function and window title
	hge->System_SetState(HGE_LOGFILE, "Space Invader.log");
	hge->System_SetState(HGE_FRAMEFUNC, FrameFunc);
	hge->System_SetState(HGE_RENDERFUNC, RenderFunc);
	hge->System_SetState(HGE_TITLE, "Space Invader 2D");

	// set video mode
	hge->System_SetState(HGE_FPS, 100);
	hge->System_SetState(HGE_WINDOWED, true);
	hge->System_SetState(HGE_SCREENWIDTH, 800);
	hge->System_SetState(HGE_SCREENHEIGHT, 600);
	hge->System_SetState(HGE_SCREENBPP, 32); // ?
	hge->System_SetState(HGE_USESOUND, false);	// when disabled game crashes

	if (hge->System_Initiate())
	{
		// load sound and textures
		sound = hge->Effect_Load("menu.wav");
		quad.tex = hge->Texture_Load("particles.png");

		// setup quad which will be used for rendering sprite
		quad.blend = BLEND_ALPHAADD | BLEND_COLORMUL | BLEND_ZWRITE;

		for (int i = 0; i < 4; i++)
		{
			// set up z co-oridinate of vertices
			quad.v[i].z = 0.5f;
			// set up color
			quad.v[i].col = 0xFFFFA000;
		}

		// setup quad's texture co-ordinates 
		quad.v[0].tx = 96.0 / 128.0;
		quad.v[0].ty = 64.0 / 128.0;
		quad.v[1].tx = 128.0 / 128.0;
		quad.v[1].ty = 64.0 / 128.0;
		quad.v[2].tx = 128.0 / 128.0;
		quad.v[2].ty = 96.0 / 128.0;
		quad.v[3].tx = 96.0 / 128.0;
		quad.v[3].ty = 96.0 / 128.0;

		// Start the system
		hge->System_Start();

		// free up the loaded texture and sound
		hge->Texture_Free(quad.tex);
		hge->Effect_Free(sound);
	}

	else
		MessageBox(NULL, hge->System_GetErrorMessage(), "Error", MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);

	// Cleanup and shut down
	hge->System_Shutdown();
	hge->Release();

	return 0;
}
*/
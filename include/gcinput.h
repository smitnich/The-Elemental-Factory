#include "input_def.h"
#include "defs.h"
//Check if the pad is going in this direction
bool checkpaddir(int dir)
{
	if (dir == D_UP && (PAD_StickY(padnum-1) >= gcsensitivity && PAD_StickX(padnum-1) <= gcsensitivity/2 && PAD_StickX(padnum-1) >= gcsensitivity*-.5)
		|| (dir == D_DOWN && (PAD_StickY(padnum-1) <= gcsensitivity*-1 && PAD_StickX(padnum-1) <= gcsensitivity/2 && PAD_StickX(padnum-1) >= gcsensitivity*-.5))
		|| (dir == D_RIGHT && (PAD_StickX(padnum-1) >= gcsensitivity && PAD_StickY(padnum-1) <= gcsensitivity/2 && PAD_StickY(padnum-1) >= gcsensitivity*-.5))
		|| (dir == D_LEFT && (PAD_StickX(padnum-1) <= gcsensitivity*-1 && PAD_StickY(padnum-1) <= gcsensitivity/2 && PAD_StickY(padnum-1) >= gcsensitivity*-.5)))
		return 1;
	else
		return D_NONE;
}
//Get the gamecube controller input
int GCInput(u16 GCButtonsDown)
{
	int leveldir = 0;
	int xdir = 0;
	int ydir = 0;
	//if (PAD_StickY(padnum-1) >= gcsensitivity && PAD_StickX(padnum-1) <= gcsensitivity/2 && PAD_StickX(padnum-1) >= gcsensitivity*-.5)
	if (checkpaddir(D_UP))
		ydir -= 1;
	//if (PAD_StickY(padnum-1) <= gcsensitivity*-1 && PAD_StickX(padnum-1) <= gcsensitivity/2 && PAD_StickX(padnum-1) >= gcsensitivity*-.5)
	if (checkpaddir(D_DOWN))
		ydir += 1;
	//if (PAD_StickX(padnum-1) >= gcsensitivity && PAD_StickY(padnum-1) <= gcsensitivity/2 && PAD_StickY(padnum-1) >= gcsensitivity*-.5)
	if (checkpaddir(D_RIGHT))
		xdir += 1;
	//if (PAD_StickX(padnum-1) <= gcsensitivity*-1 && PAD_StickY(padnum-1) <= gcsensitivity/2 && PAD_StickY(padnum-1) >= gcsensitivity*-.5)
	if (checkpaddir(D_LEFT))
		xdir -= 1;
	if (GCButtonsDown & PAD_BUTTON_START)
		return BUTTON_MENU;
	if (GCButtonsDown & PAD_TRIGGER_R)
		leveldir += 1;
	if (GCButtonsDown & PAD_TRIGGER_L)
		leveldir-= 1;
	if (leveldir <= -1)
		return BUTTON_LEVEL_PREV;
	if (leveldir >= 1)
		return BUTTON_LEVEL_NEXT;
	if (GCButtonsDown & PAD_BUTTON_B)
		return BUTTON_1;
	if (GCButtonsDown & PAD_BUTTON_A)
		return BUTTON_2;
	if (GCButtonsDown & PAD_BUTTON_LEFT)
		xdir-=1;
	if (GCButtonsDown & PAD_BUTTON_RIGHT)
		xdir += 1;
	if (xdir <= -1)
		return B_LEFT;
	if (xdir >= 1)
		return B_RIGHT;
	if (GCButtonsDown & PAD_BUTTON_UP)
		ydir-=1;
	if (GCButtonsDown & PAD_BUTTON_DOWN	)
		ydir += 1;
	if (ydir <= -1)
		return B_UP;
	if (ydir >= 1)
		return B_DOWN;
	return INPUT_NONE;
}

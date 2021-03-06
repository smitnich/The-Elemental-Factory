﻿#include "sdlFiles.h"
#include "terrain.h"
#include "objectDef.h"
#include "gfx.h"
unsigned long getTicks();
SDL_Surface *conveyor[4] = { NULL };
extern double delta, fpsModifier;
extern int conveyorSpeed;
extern int framesPerSecond;
extern bool displayName;
extern int frame;
extern int xInitial, yInitial;

bool Conveyor::requestEntry(Object* other, int objDir)
{
	return true;
}
bool Conveyor::requestExit(Object* other, int objDir)
{
	if (disabled)
		return true;
	if ((objDir == D_UP && this->dir == D_DOWN) ||
	   (objDir == D_DOWN && this->dir == D_UP) ||
	   (objDir == D_LEFT && this->dir == D_RIGHT) ||
	   (objDir == D_RIGHT && this->dir == D_LEFT))
		return false;
	else
		return true;
}
void Conveyor::whileIn(Object *other) {
	onEnter(other);
}
void Conveyor::activate()
{
	numConnectionsActive++;
	if (numConnectionsActive >= totalConnections) {
		if (!disabled) {
			disabled = true;
			disableStartTime = frame;
			moveFraction = ((frame - disabledTime) / 3) % TILE_SIZE;
		}
	}
}
void Conveyor::deactivate()
{
	numConnectionsActive--;
	if (disabled) {
		disabled = false;
		disabledTime = frame - disableStartTime;
		if (lastEntered != NULL)
			lastEntered->startMove(dir,2);
	}
}
void Conveyor::onEnter(Object *other, bool solidFound)
{
	if (!disabled && !other->hovering)
		other->startMove(dir,2);
	lastEntered = other;
}
void Conveyor::onExit(Object* other)
{
	lastEntered = NULL;
}
Conveyor::Conveyor(int direction)
{
	totalConnections = numConnectionsActive = 0;
	disableStartTime = 0;
	disabledTime = 0;
	index = 0;
	lastEntered = NULL;
	moveFraction = 0;
	disabled = false;
	isTrigger = false;
	dir = direction;
	sprite = conveyor[dir-1];
}
void Conveyor::draw(SDL_Surface *drawTo, int xTile, int yTile, int xOff, int yOff)
{
	int xWrap = 0;
	int yWrap = 0;
	if (!displayName && !disabled)
		moveFraction = ((frame - disabledTime)/3) % TILE_SIZE;
	int xStart = xTile*TILE_SIZE + xInitial + xOff;
	int yStart = yTile*TILE_SIZE + yInitial + yOff;
	switch (dir)
	{
	case D_UP:
		yWrap = TILE_SIZE-moveFraction;
		break;
	case D_DOWN:
		yWrap = moveFraction;
		break;
	case D_LEFT:
		xWrap = TILE_SIZE-moveFraction;
		break;
	case D_RIGHT:
		xWrap = moveFraction;
		break;
	}
	drawWrappedSprite(xStart, yStart, sprite, drawTo,xWrap,yWrap);
}
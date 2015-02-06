#include "SDLFiles.h"
#include "terrain.h"
#include "sprites.h"
IceFloor::IceFloor()
{
	index = -1;
	sprite = iceFloor;
}
void IceFloor::draw(SDL_Surface *drawTo, int xTile, int yTile, int xOff, int yOff){
	int xStart = xTile*TILE_SIZE + xInitial + xOff;
	int yStart = yTile*TILE_SIZE + yInitial + yOff;
	apply_surface(xStart, yStart, tiles, drawTo);
	apply_surface(xStart, yStart, sprite, drawTo);
}
void IceFloor::onEnter(Object *other)
{
	other->startMove(other->prevMove);
}
bool IceFloor::isSolid()
{
	return false;
}
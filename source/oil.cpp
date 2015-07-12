#include "SDLFiles.h"
#include "terrain.h"
#include "sprites.h"
#include "tileEnum.h"

Terrain *addTerrainChange(int index, int changeTo);
Terrain *addTerrainChange(int index, Terrain *changeTo);

Object *objectInit(unsigned int id, int idx);

SDL_Surface *spr_oilFloor = NULL;
OilFloor::~OilFloor() {
}
OilFloor::OilFloor(Terrain *within)
{
	objWithin = false;
	heated = false;
	this->within = within;
	sprite = spr_oilFloor;
}
void OilFloor::draw(SDL_Surface *drawTo, int xTile, int yTile, int xOff, int yOff){
	int xStart = xTile*TILE_SIZE + xInitial + xOff;
	int yStart = yTile*TILE_SIZE + yInitial + yOff;
	if (within != NULL)
		within->draw(drawTo, xTile, yTile, xOff, yOff);
	apply_surface(xStart, yStart, sprite, drawTo);
}
void OilFloor::onEnter(Object *other)
{
	objWithin = true;
	if (within != NULL)
		within->onEnter(other);
}
void OilFloor::onExit(Object *other) {
	objWithin = false;
	if (within != NULL)
		within->onExit(other);
	if (heated) {
		addTerrainChange(index, within);
		within = NULL;
		objectInit(1012, index);
	}
}
bool OilFloor::requestEntry(Object *other, int dir) {
	return (within != NULL && within->requestEntry(other, dir));
}
bool OilFloor::requestExit(Object *other, int dir) {
	return (within != NULL && within->requestEntry(other, dir));
}
void OilFloor::whileIn(Object *other) {
	if (within != NULL)
		within->whileIn(other);
}
void OilFloor::activate() {
	if (within != NULL)
		within->activate();
}
void OilFloor::deactivate() {
	if (within != NULL)
		within->deactivate();
}
void OilFloor::freeze() {
	IceFloor *tmp = (IceFloor*) addTerrainChange(index, m_icefloor);
	tmp->within = this->within;
}
void OilFloor::heat() {
	if (objWithin) {
		heated = true;
	}
	else {
		addTerrainChange(index, within);
		objectInit(1012, index);
	}
}
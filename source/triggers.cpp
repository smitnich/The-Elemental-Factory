#include "sdlFiles.h"
#include "terrain.h"
class Object;
#include <list>
#include "queues.h"
#include "sound.h"
SDL_Surface *spr_pressureToggle[2] = { NULL, NULL };
SDL_Surface *pressureTile = NULL;

extern std::list<Trigger*> activateQueue;
void Trigger::addConnection(Terrain *in, int _index) {
	connection tmp = { NULL, NULL, 0 };
	tmp.terrain = in;
	tmp.index = _index;
	connections.push_back(tmp);
	in->totalConnections++;
}
void Trigger::addConnection(Object *in, int _index) {
	connection tmp = { NULL, NULL, 0 };
	tmp.obj = in;
	tmp.index = _index;
	connections.push_back(tmp);
	in->totalConnections++;
}
void PressureSwitch::onEnter(Object *other, bool solidFound)
{
	if (other->hovering)
		return;
	int length = connections.size();
	for (int i = 0; i < length; i++)
	{
		activateConnection(&connections.at(i));
	} 
}
void PressureSwitch::onExit(Object *other)
{
	if (other->hovering)
		return;
	int length = connections.size();
	for (int i = 0; i < length; i++)
	{
		deactivateConnection(&connections.at(i));
	}
}
PressureSwitch::PressureSwitch()
{
	index = 0;
	isTrigger = true;
	sprite = pressureTile;
}
void ToggleSwitch::onEnter(Object *other, bool solidFound)
{
	if (other->hovering)
		return;
	enabled = !enabled;
	int length = connections.size();
	for (int i = 0; i < length; i++)
	{
		if (enabled)
			activateConnection(&connections.at(i));
		else
			deactivateConnection(&connections.at(i));
	}
	sprite = spr_pressureToggle[enabled];
	playSound(snd_switch);
}
ToggleSwitch::ToggleSwitch(bool isEnabled)
{
	enabled = isEnabled;
	index = 0;
	isTrigger = true;
	if (enabled)
		addActivateQueue(this);
	sprite = spr_pressureToggle[enabled];
}
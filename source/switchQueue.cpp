#include <list>
#include "objectDef.h"

#include "level.h"
#include "queues.h"

Object* objectInit(unsigned int id, int x, int y);

std::list<SwitchRequest> objectSwitchQueue;

void resetSwitchQueue()
{
	objectSwitchQueue.clear();
}
Object *addSwitchQueue(Object *in, int switchId)
{
	std::list<SwitchRequest>::iterator it;
	for (it = objectSwitchQueue.begin(); it != objectSwitchQueue.end(); ++it) {
		if (it->obj == in)
			return in;
	}
	SwitchRequest req;
	req.obj = in;
	req.switchTo = objectInit(switchId, in->x, in->y, false);
	objectSwitchQueue.push_back(req);
	return req.switchTo;
}
void doSwitchQueue()
{
	SwitchRequest req;
	int size = objectSwitchQueue.size();
	for (int i = 0; i < size; i++)
	{
		req = objectSwitchQueue.front();
		req.obj->die();
		getCurrentLevel()->assignObject(req.switchTo->x, req.switchTo->y, req.switchTo);
		objectSwitchQueue.pop_front();
	}
}
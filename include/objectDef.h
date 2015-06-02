#ifndef _OBJECTDEF
#define _OBJECTDEF
#include "sdlFiles.h"
#include <stdexcept>
class Object
{
public: int x, y,  objMoveDir, solid, frozen, numFrames, faceDir;
		int id;
		double moveSpeed, tempSpeed, objMoveFraction;
		bool hovering;
		int queuedMove;
		int prevMove;
		bool isPlayer;
		class Level *level;
		virtual bool isMovableBlock();
		Object();
		virtual ~Object();
		Object(Object &other, int x, int y);
		int getMoveDir();
		double getMoveFraction();
		int getX();
		int getY();
		bool objMove();
		void startMove(int dir, bool forced = false);
		virtual void drown()
		{
			die();
		}
		virtual void freeze()
		{
			frozen = true;
		}
		virtual void heat()
		{
			frozen = false;
		}
		virtual void electrocute()
		{
			if (!frozen)
				die();
		}
		//It should not be possible to have two different objects in one tile in
		//most cases, so throw an exception by default
		virtual void onEnter(Object *other, int xChange, int yChange) {
			throw std::logic_error("Multiple objects in one tile");
		}
		virtual bool allowEntry() {
			return false;
		}
		virtual void Object::draw(int moveFractionX, int moveFractionY);
		virtual void die();
		virtual void doLogic();
		virtual Object* clone(int x, int y) = 0;
		virtual void loadImages() = 0;
		//Gets the sprite to be drawn on the screen
		virtual SDL_Surface *getSprite() = 0;
		virtual bool requestEntry(Object* other, int dir);
		virtual Object* createInstance(int x, int y) = 0;
};
#include "imageMacros.h"
SDL_Surface* loadOptimizedIMG(const char *fileName);
class Crate : public Object{
public:
	OBJECT_DECLARATION(Crate,1001)
	bool isMovableBlock()
	{
		return true;
	};
	void electrocute(){

	}
	Crate(int x, int y);
	void doLogic();
	bool requestEntry(Object* other, int dir);
	Object *clone(int x, int y);
};
class ColorCrate1 : public Crate
{
public:
	OBJECT_DECLARATION(ColorCrate1, 1011)
	ColorCrate1(int x, int y);
};
class HeavyCrate : public Crate{
public:
	OBJECT_DECLARATION(HeavyCrate,1002)
	HeavyCrate(int x, int y);
	bool requestEntry(Object* other, int dir);
	Object *clone(int x, int y);
};
class Person : public Object
{
public:
	OBJECT_DECLARATION(Person,1004)
	int active;
	Person(const Person &other, int x, int y);
	Person(int x, int y);
	void makeElement(bool doSecond);
	void doLogic();
	bool requestEntry(Object* other, int dir);
	void die();
	Object *clone(int x, int y);
};
class Pickup : public Object
{
public:
	OBJECT_DECLARATION(Pickup,1009)
	void die();
	bool requestEntry(Object *other, int dir);
	Pickup(int x, int y);
	Object *clone(int x, int y);
};
class PickupWall : public Object
{
public:
	OBJECT_DECLARATION(PickupWall,1010)
	void doLogic();
	bool requestEntry(Object *other, int dir);
	PickupWall(int x, int y);
	Object *clone(int x, int y);
};
/*class IceElemental : public Object
{
public:
	OBJECT_DECLARATION(IceElemental)
	void die();
	void freeze()
	{
		return;
	}
	void electrocute()
	{
		return;
	}
	IceElemental(int x, int y, int dir);
	bool requestEntry(Object *other, int dir);
	void doLogic();
	Object *clone();
};*/
#endif
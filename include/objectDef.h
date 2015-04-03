#ifndef _OBJECTDEF
#define _OBJECTDEF
#include "sdlFiles.h"
#include "imageMacros.h"
SDL_Surface* loadOptimizedIMG(char *fileName);
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
		~Object();
		Object(Object &other, int x, int y);
		SDL_Surface *spritens[6];
		SDL_Surface *spriteew[6];
		SDL_Surface *stationary;
		int getMoveDir();
		double getMoveFraction();
		int getX();
		int getY();
		void objMove();
		void startMove(int dir, bool forced = false);
		virtual void drown()
		{
			die();
		}
		virtual void freeze()
		{
			frozen = true;
		}
		virtual void electrocute()
		{
			if (!frozen)
				die();
		}
		virtual void die();
		virtual void doLogic();
		virtual Object* clone(int x, int y) = 0;
		//Gets the sprite to be drawn on the screen
		virtual SDL_Surface *getSprite();
		virtual bool requestEntry(Object* other, int dir);
};
class Crate : public Object{
public:
	static SDL_Surface *stationary;
	static SDL_Surface *spriteew[6];
	static SDL_Surface *spritens[6];
	static void loadImages();
	bool isMovableBlock()
	{
		return true;
	};
	void electrocute(){

	}
	Crate();
	Crate(int x, int y);
	void doLogic();
	bool requestEntry(Object* other, int dir);
	Object *clone(int x, int y);
	SDL_Surface *getSprite();
};
class ColorCrate1 : public Crate
{
public:
	ColorCrate1();
	ColorCrate1(int x, int y);
};
class HeavyCrate : public Crate{
public:
	HeavyCrate(int x, int y);
	bool requestEntry(Object* other, int dir);
	Object *clone(int x, int y);
};
class Person : public Object
{
public:
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
	void die();
	bool requestEntry(Object *other, int dir);
	Pickup(int x, int y);
	Object *clone(int x, int y);
};
class PickupWall : public Object
{
public:
	void doLogic();
	bool requestEntry(Object *other, int dir);
	PickupWall(int x, int y);
	Object *clone(int x, int y);
};
class IceElemental : public Object
{
public:
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
};
#endif
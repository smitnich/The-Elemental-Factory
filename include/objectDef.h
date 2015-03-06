#ifndef _OBJECTDEF
#define _OBJECTDEF
#include "sdlFiles.h"
class Object
{
public: int x, y,  objMoveDir, solid, frozen, numFrames, faceDir;
		double moveSpeed, tempSpeed, objMoveFraction;
		int prevMove;
		bool isPlayer;
		class Level *level;
		virtual bool isMovableBlock();
		Object();
		Object(Object &other, int x, int y);
		SDL_Surface *spritens[6];
		SDL_Surface *spriteew[6];
		SDL_Surface *stationary;
		int getMoveDir();
		double getMoveFraction();
		int getX();
		int getY();
		void startMove(int dir);
		virtual void die();
		virtual void doLogic();
		virtual Object* clone(int x, int y) = 0;
		//Gets the sprite to be drawn on the screen
		SDL_Surface *getSprite();
		virtual bool requestEntry(Object* other, int dir);
};
class SolidObject : public Object {
public:
	void doLogic();
	SolidObject();
};
class Movable : public SolidObject{
public:
	Movable();
	void specialLogic();
	void doLogic();
	void objMove();
};
class Crate : public Movable{
public:
	Crate();
	bool isMovableBlock()
	{
		return true;
	};
	Crate(int x, int y);
	void doLogic();
	bool requestEntry(Object* other, int dir);
	Object *clone(int x, int y);
};
class HeavyCrate : public Crate{
public:
	HeavyCrate();
	HeavyCrate(int x, int y);
	bool requestEntry(Object* other, int dir);
	Object *clone(int x, int y);
};
class IceBall : public Movable{
public:
	~IceBall();
	IceBall();
	IceBall(int x2, int y2, int moveDir, int moveFraction);
	void objMove();
	void doLogic();
	bool requestEntry(Object* other, int dir);
	Object *clone(int x, int y);
};
class Person : public Movable
{
public:
	int active;
	Person(const Person &other, int x, int y);
	Person(int x, int y);
	void makeElement(bool doSecond);
	char element;
	void doLogic();
	bool requestEntry(Object* other, int dir);
	void die();
	Object *clone(int x, int y);
};
#endif
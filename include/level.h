#ifndef _LEVEL
#define _LEVEL
#include "terrain.h"
#include <vector>
#include "defs.h"

extern const std::string LevelStrings[];

class Level
{
	public:
	int width;
	int height;
	unsigned int pickupCount;
	std::vector<unsigned int> origMapLayer;
	std::vector<unsigned int> origObjectLayer;
	std::vector<Terrain *> mapLayer;
	std::vector<Object *> objectLayer;
	std::vector<int> receivers[MAX_CONNECTIONS];
	std::vector<int> senders[MAX_CONNECTIONS];
	char **connectionLayer;
	Level(FILE* inFile, int levelNum);
	void loadAllLayers(char *buffer,FILE *inFile);
	void loadObjects();
	int convertIndex(int x, int y);
	void convertIndex(int input, int &x, int &y);
	void loadLayer(FILE *inFile, std::string str, int xSize, int ySize);
	void loadMapLayer(FILE *inFile, std::vector<unsigned int> *layer,int xSize, int ySize);
	void reloadMapLayer();
	bool assignObject(int x, int y, Object *obj);
	bool assignObject(int index, Object *obj);
	Object* getObject(int x, int y);
	Object *getObject(int index);
	Terrain* getTerrain(int x, int y);
	void loadConnections(FILE *inFile, int xSize, int ySize);
	void makeConnections();
	void checkTerrain();
};
Level *getCurrentLevel();
Object* objectInit(unsigned int id, int x, int y, bool addToLevel = true);
Object* objectInit(unsigned int id, int idx, bool addToLevel = true);
std::string constructLevelName(int);
extern class Level *allLevels[MAX_LEVEL];

class Terrain *instantiateTerrain(int input, int i);
unsigned char lookupWall(int index);
void switchLevel(int levelNum);
std::string constructLevelName(int levelNum);
class Level* getCurrentLevel();
bool loadLevel(std::string fileName, int levelNum);
void restartLevel();
void prevLevel();
void nextLevel();
#endif
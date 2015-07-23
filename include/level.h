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
	int senders[MAX_CONNECTIONS];
	char **connectionLayer;
	Level(FILE* inFile, int levelNum);
	void loadAllLayers(char *buffer,FILE *inFile);
	void loadObjects();
	int convertIndex(int x, int y);
	void loadLayer(FILE *inFile, std::string str, int xSize, int ySize);
	void loadMapLayer(FILE *inFile, std::vector<unsigned int> *layer,int xSize, int ySize);
	void reloadMapLayer();
	bool assignObject(int x, int y, Object *obj);
	Object* getObject(int x, int y);
	Terrain* getTerrain(int x, int y);
	void loadConnections(FILE *inFile, int xSize, int ySize);
	void makeConnections();
	void checkTerrain();
};
Level *getCurrentLevel();
#endif
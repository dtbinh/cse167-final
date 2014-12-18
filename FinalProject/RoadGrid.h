#ifndef _ROADGRID_H_
#define _ROADGRID_H_
#define _CRTDBG_MAP_ALLOC
#define _CRT_SECURE_NO_DEPRECATE
#include "Matrix4.h"
#include "CreateSkyscrapper.h"
#include "Building.h"

#include <time.h>       
#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* srand, rand */
#include <ctime>
#include <vector>

using namespace std;

class RoadGrid{

protected:
	float xPosition, yPosition;
	GLuint texture[5];     // storage for five texture
	bool load = true;
	float randomHeights[100];
	float randomHeightsHouses[10][10][14];
	float randomHeightsTowers[4][4][4];
	float randomHeightsSmallTowers[11];


	vector<Building*> buildings;

	// road textures
	//GLuint road, roadEmpty, roadT, roadTurn, roadX;

public:
	float randomWidth;
	float randomHeight;

	RoadGrid();
	~RoadGrid();
	CreateSkyscrapper* tester = new CreateSkyscrapper();

	//Where all the texture files are stored
	unsigned char* regRoad;
	unsigned char* regRoadRotated;
	unsigned char* road;
	unsigned char* roadEmpty;
	unsigned char* roadT;
	unsigned char* roadTurn;
	unsigned char* roadTurnLarge;
	unsigned char* roadX;
	unsigned char* parkingLot;
	unsigned char* Marsh;
	unsigned char* windows;

	double mult = 16;

	float createRandomHeight(int);
	float createRandomWidth(int);
	void createGrid(float, float);
	void render();
	void loadTexture();
	void createCity(float);

	void createBlock(float, float, int);
	void createDowntown(float, float, int, int);
	void createMidtown(float, float, int);
	void renderSkyscrapper(float, float, float, float);
	void renderBuildings(float, float, float, float);

	void loadRawTexture(GLuint tex, const char *filename, int width, int height);

	vector<Building*>& getBuildings() {
		return buildings;
	}
};

#endif


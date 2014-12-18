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
	float randomHeights[900];

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
	
	float createRandomHeight(int);
	float createRandomWidth(int);
	void createGrid(float, float, int pid);
	void render(int);
	void loadTexture();
	void createCity(float);

	void loadRawTexture(GLuint tex, const char *filename, int width, int height);

	vector<Building*>& getBuildings() {
		return buildings;
	}
};

#endif


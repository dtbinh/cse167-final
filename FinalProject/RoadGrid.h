#ifndef _ROADGRID_H_
#define _ROADGRID_H_
#define _CRTDBG_MAP_ALLOC
#define _CRT_SECURE_NO_DEPRECATE
#include "Matrix4.h"
#include "CreateSkyscrapper.h"
#include "GL/glut.h"
#include <time.h>       
#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* srand, rand */
#include <ctime>
class RoadGrid{

protected:
	float xPosition, yPosition;
	GLuint texture[5];     // storage for five texture
	bool load = true;
	float randomHeights[900];

public:
	float randomWidth;
	float randomHeight;

	RoadGrid();
	~RoadGrid();
	CreateSkyscrapper* tester = new CreateSkyscrapper();

	int twidth, theight;   // texture width/height [pixels]
	unsigned char* tdata1;  // texture pixel data
	
	float createRandomHeight(int);
	float createRandomWidth(int);
	void createGrid(float, float);
	void render();
	void loadTexture();
	void createCity(float);
};

#endif


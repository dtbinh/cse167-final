#ifndef _SKYSCRAPPER_H_
#define _SKYSCRAPPER_H_
#define _CRTDBG_MAP_ALLOC
#define _CRT_SECURE_NO_DEPRECATE
#include "Matrix4.h"
#include "GL/glut.h"
#include <time.h>       

class CreateSkyscrapper{

protected:
	int twidth, theight;   // texture width/height [pixels]
	unsigned char* tdata1;  // texture pixel data
	float xPosition, yPosition;

public:
	CreateSkyscrapper();
	~CreateSkyscrapper();
	void renderSkyscrapper(float, float, float, float);
	unsigned char* loadPPM(const char*, int&, int&);
	void loadTexture();
};

#endif


#ifndef _PARTICLES_H_
#define _PARTICLES_H_
#include "Matrix4.h"
#include "CreateSkyscrapper.h"
#include "GL/glut.h"
#include <time.h>       
#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* srand, rand */
#include <ctime>
#include "Vector3.h"

#define MAX_PARTICLES 1000
#define MAX_PARTICLE_AGE 100
#define MAX_BOUNCE_COUNT 10

class Particles{

protected:

	struct
		PARTICLE {
		float X, Y, Z;
		float sX, sY, sZ;
		float tX, tY, tZ;
		float R, B, G;
		bool Active;
		int Age;
		int MaxAge;
		int BounceCount;
	} Part[MAX_PARTICLES];

public:
	Particles();
	~Particles();
	void InitParticles();
	void ActivateParticles();
	void AdjustParticles();
	void RenderParticles();


};

#endif


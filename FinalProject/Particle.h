#pragma once
#include <vector>
#include "SGGeode.h"

using namespace std;

class Particle {
private:
	void move(GLfloat x, GLfloat y, GLfloat z);
public:
	GLfloat xpos, ypos, zpos; // position
	GLfloat xspeed, yspeed, zspeed; // velocity
	GLfloat r, g, b, a;	// color and opacity
	int lifetime, age;
	GLfloat size;
	bool alive;

	Particle();
	Particle(GLfloat x, GLfloat y, GLfloat z, int life);
	virtual ~Particle();

	GLfloat randVelocity();
	void update();
};

class ParticleEmitter : SGGeode {
private:
	GLfloat xpos, ypos, zpos; // position
	unsigned int amount; // number of particles
	int particleLife; // mean lifetime of particles
	vector<Particle*> particles; // list of particles

public:
	ParticleEmitter();
	ParticleEmitter(GLfloat x, GLfloat y, GLfloat z, int numParticles, int life);
	virtual ~ParticleEmitter();

	void update();
	void render();
};
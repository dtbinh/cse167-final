#include "Particle.h"
#include <random>

static const float particle_lifetime_std_dev = 100.0f;
static const float p_color[] = { 0.0f, 0.0f, 1.0f, 1.0f }; // RGBA
static const float gravity = 0.05f;

// seed random number generator (normal distribution around {life})
std::default_random_engine gen;

Particle::Particle() {
	xpos = ypos = zpos = 0.0f;
	xspeed = yspeed = zspeed = 0.0f;
	lifetime = 0;
	age = 0;
	alive = false;
}

Particle::Particle(GLfloat x, GLfloat y, GLfloat z, int life) : lifetime(life) {

	std::normal_distribution<float> xdist((float)x, 25.0);
	std::normal_distribution<float> zdist((float)z, 25.0);
	xpos = xdist(gen);
	ypos = y;
	zpos = zdist(gen);

	r = p_color[0];
	g = p_color[1];
	b = p_color[2];
	a = p_color[3];

	age = -(rand() % life);

	xspeed = randVelocity();
	yspeed = -0.9f;
	zspeed = randVelocity();

	size = 2.0f;

	alive = true;
}


Particle::~Particle() {
}

GLfloat Particle::randVelocity() {
	int direction = rand() % 2 ? 1 : -1;
	float magnitude = ((float)rand() / RAND_MAX) * 0.5;
	return magnitude * direction;
}

void Particle::update() {
	age++;
	if (age < 0) return;
	if (age > lifetime) // if particle is old, die
		alive = false;

	// apply gravity
	//if (ypos > 0.0) {
		if (yspeed < 5.0f) yspeed -= gravity;
		xspeed *= 0.5;
		zspeed *= 0.5;
		
		move(xpos + xspeed, ypos + yspeed, zpos + zspeed);
	//}
}

void Particle::move(GLfloat x, GLfloat y, GLfloat z) {
	// hit ground -> bounce
	if (ypos <= 0.0) {
		float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		yspeed *= -0.4 * r;
	}
	xpos += xspeed;
	ypos += yspeed;
	zpos += zspeed;
}


ParticleEmitter::ParticleEmitter() {
}

ParticleEmitter::ParticleEmitter(GLfloat x, GLfloat y, GLfloat z, int numParticles, int life) : xpos(x), ypos(y), zpos(z) {
	amount = numParticles;
	particleLife = life;
	particles = vector<Particle*>();

	std::normal_distribution<float> dist((float)life, particle_lifetime_std_dev);

	// create particles
	for (int i = 0; i < (int)amount; ++i) {
		particles.push_back(new Particle(x, y, z, dist(gen)));
	}
}

ParticleEmitter::~ParticleEmitter() {
	for (auto it = particles.begin(); it != particles.end(); ++it) {
		delete *it;
	}
	particles.clear();
}

void ParticleEmitter::update() {
	for (auto it = particles.begin(); it != particles.end(); ) {
		// update particle
		

		if (!(*it)->alive) {
			// if particle is dead, delete it
			delete (*it);
			it = particles.erase(it);
		} else {
			(*it)->update();
			++it;
		}
	}
	// add new particles to replace deleted ones
	std::normal_distribution<float> dist((float)particleLife, particle_lifetime_std_dev);
	while (particles.size() < amount) {
		particles.push_back(new Particle(xpos, ypos, zpos, dist(gen)));
	}
}

void ParticleEmitter::render() {
	glPushMatrix();
	glPointSize(3.0f);
	glColor3f(p_color[0], p_color[1], p_color[2]);
	glBegin(GL_POINTS);
	for (auto it = particles.begin(); it != particles.end(); ++it) {
		if ((*it)->age >= 0)
			glVertex3f((*it)->xpos, (*it)->ypos, (*it)->zpos);
	}
	glEnd();
	glPopMatrix();
}
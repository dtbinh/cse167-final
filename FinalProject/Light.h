#pragma once
#include "Vector3.h"
#include "Matrix4.h"
#include <GL\glut.h>

class Light {
protected:
	GLfloat diffuse[4];
	GLfloat specular[4];
	GLfloat ambient[4];

	GLenum glLight;
	int lightNum;

	Vector3 axis;

	bool visible;
public:
	Light(int, GLfloat*, GLfloat*, GLfloat*);

	virtual ~Light();

	void enable();
	void disable();

	void setDiffuse(GLfloat*);
	void setSpecular(GLfloat*);
	void setAmbient(GLfloat*);

	void setPos(GLfloat* pos) { glLightfv(glLight, GL_POSITION, pos); }

	// Spotlight setters
	void setDir(GLfloat* dir) { glLightfv(glLight, GL_SPOT_DIRECTION, dir); }
	void setExp(GLfloat e) { glLightf(glLight, GL_SPOT_EXPONENT, e); }
	void setCutoff(GLfloat c) { glLightf(glLight, GL_SPOT_CUTOFF, c); }

	// Attenuation setters
	void setConstantAttn(GLfloat a) { glLightf(glLight, GL_CONSTANT_ATTENUATION, a); }
	void setLinearAttn(GLfloat a) { glLightf(glLight, GL_LINEAR_ATTENUATION, a); }
	void setQuadAttn(GLfloat a) { glLightf(glLight, GL_QUADRATIC_ATTENUATION, a); }

	void setAxis(Vector3& a) { axis = a; }
	Vector3& getAxis() { return axis; }

	bool isVisible() { return visible; }
	void setVisible(bool v) { visible = v; }

};

class PointLight : public Light {
private:
	GLfloat angle;
	GLfloat pos[4];
public:
	PointLight(int, GLfloat*, GLfloat*, GLfloat*, GLfloat*);
	virtual ~PointLight();
	void enable();
	void disable();
	void draw();
	void setPosition(GLfloat*);
	GLfloat* getPosition() { return pos; }
	GLfloat getAngle() { return angle; }
	void setAngle(GLfloat a) { angle = a; }
};

class SpotLight : public Light {
private:
	GLfloat pos[4];
	GLfloat dir[3];
	GLfloat exp, cutoff;
	GLfloat angle;
public:
	SpotLight(int, GLfloat*, GLfloat*, GLfloat*, GLfloat*, GLfloat*, GLfloat, GLfloat);
	virtual ~SpotLight();
	void enable();
	void disable();
	void draw();
	void setPosition(GLfloat*);
	GLfloat* getPosition() { return pos; }
	void setDirection(GLfloat*);
	GLfloat* getDirection() { return dir; }
	GLfloat getAngle() { return angle; }
	void setAngle(GLfloat a) { angle = a; }
};
#pragma once
#include "Vector4.h"
#include "GL\glut.h"

class Material {
private:
	GLfloat diffuse[4];
	GLfloat specular[4];
	GLfloat ambient[4];
	GLfloat color[3];
	GLfloat shininess;

	GLenum fb; // GL_FRONT or GL_FRONT_AND_BACK

public:
	Material();
	Material(GLfloat* diffuse, GLfloat *specular, GLfloat *ambient, GLfloat shininess, GLenum frontback, GLfloat *color);
	Material(const Material& m);
	virtual ~Material();

	void setDiffuse(GLfloat *d) { glMaterialfv(fb, GL_DIFFUSE, d); }
	void setSpecular(GLfloat *s) { glMaterialfv(fb, GL_SPECULAR, s); }
	void setAmbient(GLfloat *a) { glMaterialfv(fb, GL_AMBIENT, a); }
	void setShininess(GLfloat *s) { glMaterialfv(fb, GL_SHININESS, s); }
	void apply();

	Material& operator=(const Material&);
};


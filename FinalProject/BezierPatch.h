#pragma once
#include <vector>
#include "SGGeode.h"
#include "Material.h"


static const int detail = 100; // number of points on each curve

class BezierPatch : public SGGeode {
protected:
	float time, inc; // used for updating
	
	GLfloat cp[4][4][3]; // control points

	GLfloat *indices[detail][detail]; // vertices on curves
	GLfloat *normals[detail][detail];	// normals on curves

	Material *material;


	GLfloat* calcU(float t, int row);
	GLfloat* calcV(float t, GLfloat** pts);
	GLfloat* calc(float u, float v);

	GLfloat* calcWithDelta(float u, float v);
	GLfloat* calcNormU(float t, int row);

	GLfloat* calcNormal(float t1, float t2);
	GLfloat* Bez(float t, GLfloat *p0, GLfloat *p1, GLfloat *p2, GLfloat *p3);

public:
	BezierPatch();
	BezierPatch(GLfloat[4][4][3]);
	virtual ~BezierPatch();

	void set(GLfloat[4][4][3]);
	void setMaterial(Material m);

	void print();

	void render();

	void update();
};


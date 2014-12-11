#include "BezierCurve.h"
#include "GL\glut.h"

BezierCurve::BezierCurve(Vector3 *p0, Vector3 *p1, Vector3 *p2, Vector3 *p3) : _p0(p0), _p1(p1), _p2(p2), _p3(p3) {
	/*controlPoints.push_back(p0);
	controlPoints.push_back(p1);
	controlPoints.push_back(p2);
	controlPoints.push_back(p3);*/

	cp[0][0] = p0->x();
	cp[0][1] = p0->y();
	cp[0][2] = p0->z();

	cp[1][0] = p1->x();
	cp[1][1] = p1->y();
	cp[1][2] = p1->z();
	
	cp[2][0] = p2->x();
	cp[2][1] = p2->y();
	cp[2][2] = p2->z();

	cp[3][0] = p3->x();
	cp[3][1] = p3->y();
	cp[3][2] = p3->z();
	
	// create matrix
	Matrix4 G(p0->x(), p1->x(), p2->x(), p3->x(),
		p0->y(), p1->y(), p2->y(), p3->y(),
		p0->z(), p1->z(), p2->z(), p3->z(),
		0.0f, 0.0f, 0.0f, 0.0f);
	Matrix4 B(-1.0f, 3.0f, -3.0f, 1.0f,
		3.0f, -6.0f, 3.0f, 0.0f,
		-3.0f, 3.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f, 0.0f);

	bezMatrix = new Matrix4();
	bezMatrix->multiply(B, G);	// maybe order should be switched????
}


BezierCurve::~BezierCurve() {
	delete _p0;
	delete _p1;
	delete _p2;
	delete _p3;
	delete bezMatrix;
	controlPoints.clear();
}

std::vector<Vector3*>& BezierCurve::points() {
	return controlPoints;
}

const std::vector<Vector3*>& BezierCurve::points() const {
	return controlPoints;
}

void BezierCurve::render() {
	glColor3f(1.0, 1.0, 1.0);
	glMap1f(GL_MAP1_VERTEX_3, 0.0f, 1.0f, 3, 4, &cp[0][0]);
	glBegin(GL_LINE_STRIP);
	for (float t = 0.0f; t <= 1.0f; t += 0.01f) {
		glEvalCoord1f((GLfloat)t);
	}
	glEnd();

	// Control Points
	glPointSize(5.0);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POINTS);
		for (int i = 0; i < 4; ++i) {
			glVertex3fv(&cp[i][0]);
		}
	glEnd();

	// Lines
	glColor3f(0.0, 0.5, 1.0);
	glBegin(GL_LINE_STRIP);
		for (int i = 0; i < 4; ++i) {
			glVertex3fv(&cp[i][0]);
		}
	glEnd();

}
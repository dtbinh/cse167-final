#include "CreateSkyscrapper.h"

CreateSkyscrapper::CreateSkyscrapper(){}

CreateSkyscrapper::~CreateSkyscrapper(){}

void CreateSkyscrapper::renderSkyscrapper(float width, float height, float xCoord, float zCoord){

	glBegin(GL_QUADS);
	
		//glColor3f(0.0, 0.0, 1.0);

		glNormal3f(0.0, 0.0, 1.0);
		glVertex3f((-1.0 * width) + xCoord, 1.0 + height, (1.0 * width) + zCoord);
		glVertex3f((1.0 * width) + xCoord, 1.0 + height, (1.0 * width) + zCoord);
		glVertex3f((1.0 * width) + xCoord, -0.9, (1.0 * width) + zCoord);
		glVertex3f((-1.0 * width) + xCoord, -0.9, (1.0 * width) + zCoord);

		//// Draw left side:
		glNormal3f(-1.0, 0.0, 0.0);
		glVertex3f((-1.0 * width) + xCoord, 1.0 + height, (1.0 * width) + zCoord);
		glVertex3f((-1.0 * width) + xCoord, 1.0 + height, -(1.0 * width) + zCoord);
		glVertex3f((-1.0 * width) + xCoord, -0.9, -(1.0 * width) + zCoord);
		glVertex3f((-1.0 * width) + xCoord, -0.9, (1.0 * width) + zCoord);

		//// Draw right side:
		glNormal3f(1.0, 0.0, 0.0);
		glVertex3f((1.0 * width) + xCoord, 1.0 + height, (1.0 * width) + zCoord);
		glVertex3f((1.0 * width) + xCoord, 1.0 + height, -(1.0 * width) + zCoord);
		glVertex3f((1.0 * width) + xCoord, -0.9, -(1.0 * width) + zCoord);
		glVertex3f((1.0 * width) + xCoord, -0.9, (1.0 * width) + zCoord);

		//// Draw back face:
		glNormal3f(0.0, 0.0, -1.0);
		glVertex3f((-1.0 * width) + xCoord, 1.0 + height, -(1.0 * width) + zCoord);
		glVertex3f((1.0 * width) + xCoord, 1.0 + height, -(1.0 * width) + zCoord);
		glVertex3f((1.0 * width) + xCoord, -0.9, -(1.0 * width) + zCoord);
		glVertex3f((-1.0 * width) + xCoord, -0.9, -(1.0 * width) + zCoord);

		//// Draw top side:
		glNormal3f(0.0, 1.0, 0.0);
		glVertex3f((-1.0 * width) + xCoord, 1.0 + height, (1.0 * width) + zCoord);
		glVertex3f((1.0 * width) + xCoord, 1.0 + height, (1.0 * width) + zCoord);
		glVertex3f((1.0 * width) + xCoord, 1.0 + height, (-1.0 * width) + zCoord);
		glVertex3f((-1.0 * width) + xCoord, 1.0 + height, (-1.0 * width) + zCoord);

		// Draw bottom side:
		glNormal3f(0.0, -1.0, 0.0);
		glVertex3f((-1.0 * width) + xCoord, -0.9, (-1.0 * width) + zCoord);
		glVertex3f((1.0 * width) + xCoord, -0.9, (-1.0 * width) + zCoord);
		glVertex3f((1.0 * width) + xCoord, -0.9, (1.0 * width) + zCoord);
		glVertex3f((-1.0 * width) + xCoord, -0.9, (1.0 * width) + zCoord);

	glEnd();

}

void CreateSkyscrapper::renderCylinder(float width, float height, float xCoord, float zCoord){
	GLUquadricObj *obj = gluNewQuadric();

	glRotated(90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(obj, 1.0, 1.0, 10, 30, 30);


}

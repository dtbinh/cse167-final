#include "GLee.h"
#include <GL\glut.h>

using namespace std;

int WIN_WIDTH = 1000;
int WIN_HEIGHT = 700;

/* OpenGL display callback function */
void displayCallback() {
	glEnable(GL_LIGHTING);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // clear color and depth buffers
	glMatrixMode(GL_MODELVIEW);


	glFlush();
	glutSwapBuffers();
}

/* OpenGL idle callback function */
void idleCallback() {
	displayCallback();
}

/* OpenGL reshape callback function */
void reshapeCallback(int w, int h) {
	WIN_WIDTH = w;
	WIN_HEIGHT = h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (double)WIN_WIDTH / (double)WIN_HEIGHT, 1.0, 1000.0);
	glMatrixMode(GL_MODELVIEW);
}

/* Input Handling Functions */
void processNormalKeys(unsigned char key, int x, int y) {
	switch (key) {
	case 27: // ESC
		exit(0);
	}
}

void releaseNormalKeys(unsigned char key, int x, int y) {
}

void processSpecialKeys(int key, int x, int y) {
}

void mouseButton(int button, int state, int x, int y) {
}

void mouseMove(int x, int y) {
}


int main(int argc, char *argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);
	glutCreateWindow("CSE167 - Final Project");

	glEnable(GL_DEPTH_TEST);
	glClear(GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glShadeModel(GL_SMOOTH);
	glMatrixMode(GL_PROJECTION);

	// Lighting
	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);
	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

	// Callback functions
	glutDisplayFunc(displayCallback);
	glutReshapeFunc(reshapeCallback);
	glutIdleFunc(idleCallback);

	// Input Handlers
	glutIgnoreKeyRepeat(1);
	glutKeyboardFunc(processNormalKeys);
	glutKeyboardUpFunc(releaseNormalKeys);
	glutSpecialFunc(processSpecialKeys);

	// Mouse movement
	glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMove);


	glutMainLoop();

	return 0;
}
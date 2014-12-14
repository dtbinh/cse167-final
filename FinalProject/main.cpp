#include "Shader.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <GL\glut.h>
#include <math.h>
#include <algorithm>
#include <time.h>
#include "TimeManager.h"
#include "PiecewiseCurve.h"
#include "BezierPatch.h"
#include "Cubemap.h"
#include "Camera.h"
#include "Light.h"
#include "Material.h"

using namespace std;

const float DEG_TO_RADS = 3.141592654f / 180.0f; // convertion of 1 degree to radians

/** Window measurements */
int WIN_WIDTH = 1000;
int WIN_HEIGHT = 700;
GLint midWinX = WIN_WIDTH / 2.0f;
GLint midWinY = WIN_HEIGHT / 2.0f;

/** Skybox properties */
Cubemap *skybox;
Shader *skyShader;
GLuint skyShaderCameraPosition; // used by shader


/** Camera properties */
Camera *camera;

// angle of rotation for the camera direction
float camXAngle = 0.0f;	// relative to x-axis (i.e. vertical angle)
float camYAngle = 0.0f; // relative to y-axis (i.e. horizontal angle)

// XYZ position of the camera
float camXPos = 0.0f, camYPos = 10.0f, camZPos = 30.0f;

// movement speed of the camera
float camXSpeed = 0.0f, camYSpeed = 0.0f, camZSpeed = 0.0f;
GLfloat speed = 1.0f; // adjust to change movement speed

// Directional movement
bool moveForward = false, moveBackward = false, moveLeft = false, moveRight = false;
bool moveUp = false, moveDown = false;

/** Bezier surface */
BezierPatch *bezPatch;


/** Material properties */
GLfloat emptyMat[] = { 0.0, 0.0, 0.0, 1.0 };	// empty vector to occupy properties we don't want a material to have
GLfloat ambientMat[] = { 0.7, 0.7, 0.7, 1.0 };	// ambient material property
GLfloat specularMat[] = { 1.0, 1.0, 1.0, 1.0 };	// specular material property
GLfloat diffuseMat[] = { 0.5, 0.5, 0.5, 1.0 };	// diffuse material property
GLfloat white[] = { 1.0, 1.0, 1.0 };		// white material color
GLfloat red[] = { 1.0, 0.0, 0.0 };			// red material color
GLfloat green[] = { 0.0, 1.0, 0.0 };		// green material color
GLfloat blue[] = { 0.0, 0.0, 1.0 };			// blue material color

/** Lights */
PointLight *pointLight0;

/** Camera track */
PiecewiseCurve *pc;


/* Adjust camera position based off mouse and keyboard input */
void calcCameraMovement() {
	float xMovement = 0.0f, yMovement = 0.0f, zMovement = 0.0f;

	if (moveForward) {
		float pitch = cos(camXAngle * DEG_TO_RADS);
		xMovement += speed * sin(camYAngle * DEG_TO_RADS) * pitch;
		yMovement += speed * -sin(camXAngle * DEG_TO_RADS);
		float yaw = cos(camXAngle * DEG_TO_RADS);
		zMovement += speed * -cos(camYAngle * DEG_TO_RADS) * yaw;
	}

	if (moveBackward) {
		float pitch = cos(camXAngle * DEG_TO_RADS);
		xMovement += speed * -sin(camYAngle * DEG_TO_RADS) * pitch;
		yMovement += speed * sin(camXAngle * DEG_TO_RADS);
		float yaw = cos(camXAngle * DEG_TO_RADS);
		zMovement += speed * cos(camYAngle * DEG_TO_RADS) * yaw;
	}

	if (moveLeft) {
		float camYAngleRad = camYAngle * DEG_TO_RADS;
		xMovement += -speed * cos(camYAngleRad);
		zMovement += -speed * sin(camYAngleRad);
	}

	if (moveRight) {
		float camYAngleRad = camYAngle * DEG_TO_RADS;
		xMovement += speed * cos(camYAngleRad);
		zMovement += speed * sin(camYAngleRad);
	}

	// limit movement speed (so diagonal doesn't make you go faster)
	if (xMovement > speed) xMovement = speed;
	if (xMovement < -speed) xMovement = -speed;
	if (yMovement > speed) yMovement = speed;
	if (yMovement < -speed) yMovement = -speed;
	if (zMovement > speed) zMovement = speed;
	if (zMovement < -speed) zMovement = -speed;

	// apply to camera speed
	camXSpeed = xMovement;
	camYSpeed = yMovement;
	camZSpeed = zMovement;

	// update camera position
	camXPos += camXSpeed;
	camYPos += camYSpeed;
	camZPos += camZSpeed;

	// set camera matrix
	camera->set(camXPos, camYPos, camZPos,
		camXPos + sin(camYAngle * DEG_TO_RADS), camYPos + -tan(camXAngle * DEG_TO_RADS), camZPos + -cos(camYAngle * DEG_TO_RADS),
		0.0f, 1.0f, 0.0f);

	
	// If camera moved, display new position
	if (moveForward || moveBackward || moveLeft || moveRight) {
		camera->getCenterOfProjection().print("Camera position: ");
	}
}

/* Adjust camera position along piecewise Bezier curve as a function of time */
void moveCameraAlongTrack(float t) {
	
}


/* OpenGL display callback function */
void displayCallback() {

	// show fps in console
	TimeManager::Instance().CalculateFrameRate(true);

	glEnable(GL_LIGHTING);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // clear color and depth buffers
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();


	// update camera
	calcCameraMovement();
	glutWarpPointer(midWinX, midWinY); // moves (hidden) cursor to middle of window
	
	// set OpenGL matrix
	gluLookAt(camera->getCenterOfProjection().x(), camera->getCenterOfProjection().y(), camera->getCenterOfProjection().z(),
	camera->getLookAtPoint().x(), camera->getLookAtPoint().y(), camera->getLookAtPoint().z(),
	camera->getUp().x(), camera->getUp().y(), camera->getUp().z());

	// alternate way to update the matrix
	//glRotatef(camXAngle, 1.0f, 0.0f, 0.0f); // rotation around x-axis
	//glRotatef(camYAngle, 0.0f, 1.0f, 0.0f); // rotation around y-axis
	//glTranslatef(-camXPos, -camYPos, -camZPos);

	
	// render skybox
	glPushAttrib(GL_ENABLE_BIT);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_BLEND);

	skyShader->bind();
	glUniform3fvARB(skyShaderCameraPosition, 1, camera->getCenterOfProjection().asArray());
	skybox->render();
	skyShader->unbind();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_BLEND);

	// render lighting
	pointLight0->enable();
	pointLight0->draw();

	// render Bezier patch
	bezPatch->render();

	//bc->render();
	pc->render();

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
	GLint midWinX = WIN_WIDTH / 2.0f;
	GLint midWinY = WIN_HEIGHT / 2.0f;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (double)WIN_WIDTH / (double)WIN_HEIGHT, 1.0, 1000.0);
	glMatrixMode(GL_MODELVIEW);
}

/* Input Handling Functions */
void processNormalKeys(unsigned char key, int x, int y) {
	switch (key) {
	// WASD movement
	case 'w': moveForward = true; break;
	case 's': moveBackward = true; break;
	case 'a': moveLeft = true; break;
	case 'd': moveRight = true; break;

	case 27: // ESC
		exit(0);
	}
}

void releaseNormalKeys(unsigned char key, int x, int y) {
	switch (key) {
	// WASD movement
	case 'w': moveForward = false; break;
	case 's': moveBackward = false; break;
	case 'a': moveLeft = false; break;
	case 'd': moveRight = false; break;
	}
}

void processSpecialKeys(int key, int x, int y) {
}

/* OpenGL mouse function */
void mouseButton(int button, int state, int x, int y) {
}

/* Passive mouse motion callback function  (camera control) */
void mouseMove(int x, int y) {
	GLfloat sensitivity = 10.0f;

	int xMove = x - midWinX;
	int yMove = y - midWinY;

	camXAngle += yMove / sensitivity;
	camYAngle += xMove / sensitivity;

	// limit vertical rotation (stop at straight up and straight down)
	if (camXAngle <= -90.0f) camXAngle = -89.9f;
	if (camXAngle >= 90.0f) camXAngle = 89.9f;
	// keep horizontal rotation between -180 and 180 degrees (just so values are easier to interpret)
	if (camYAngle < -180.0f) camYAngle += 360.0f;
	if (camYAngle > 180.0f) camYAngle -= 360.0f;
}



int main(int argc, char *argv[]) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);
	glutCreateWindow("CSE167 - Final Project");
	//glutFullScreen();		// needs to be enabled in final version

	glEnable(GL_DEPTH_TEST);
	glClear(GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glShadeModel(GL_SMOOTH);
	glMatrixMode(GL_PROJECTION);

	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_TEXTURE_2D);

	// Lighting
	glEnable(GL_LIGHTING);

	/* pointLight0 */
	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };			// ambient property for pointLight0
	GLfloat pointSpecular[] = { 1.0, 1.0, 1.0, 1.0 };	// specular property for pointLight0
	GLfloat pointDiffuse[] = { 1.0, 1.0, 1.0, 1.0 };	// diffuse property for pointLight0
	GLfloat pointPos[] = { 0.0, 20.0, 0.0, 1.0 };		// position of pointLight0
	pointLight0 = new PointLight(0, pointDiffuse, pointSpecular, ambient, pointPos);

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
	glutPassiveMotionFunc(mouseMove); // rotates camera when no buttons are pressed
	glutSetCursor(GLUT_CURSOR_NONE); // hides cursor

	// Initialize camera
	camera = new Camera();

	// Initialize skybox
	skybox = new Cubemap("../res/textures/calm_right.raw",
		"../res/textures/calm_left.raw",
		"../res/textures/calm_top.raw",
		"../res/textures/calm_bottom.raw",
		"../res/textures/calm_front.raw",
		"../res/textures/calm_back.raw",
		512, 512);

	// Initialize shaders
	skyShader = new Shader("../shaders/sky.vert", "../shaders/sky.frag", true);
	skyShader->printLog();
	skyShaderCameraPosition = glGetUniformLocation(skyShader->getPid(), "CameraPosition");


	// Camera track (temporary)
	GLfloat curvepoints[3][4][3] = {
			{
				{ 0.0, 25.0, 50.0 }, { -50.0, 50.0, 30.0 },
				{ -50.0, 20.0, -10.0 }, { -20.0, 30.0, -30.0 }
			},
			{
				{ -20.0, 30.0, -30.0 }, { 10.0, 40.0, -50.0 },
				{ 10.0, 50.0, -40.0 }, { 30.0, 35.0, -10.0 }
			},
			{
				{ 30.0, 35.0, -10.0 }, { 50.0, 20.0, 20.0 },
				{ 50.0, 0.0, 70.0 }, { 0.0, 25.0, 50.0 }
			}
	};
	pc = new PiecewiseCurve(3, curvepoints);

	// Initialize Bezier patch (ground)
	GLfloat controlPoints[4][4][3] = {
			{
				{ 100, 0, 100 },
				{ 50, 0, 100 },
				{ -50, 0, 100 },
				{ -100, 0, 100 }
			},
			{
				{ 100, 0, 50 },
				{ 50, 0, 50 },
				{ -50, 0, 50 },
				{ -100, 0, 50 }
			},
			{
				{ 100, 0, -50 },
				{ 50, 0, -50 },
				{ -50, 0, -50 },
				{ -100, 0, -50 }
			},
			{
				{ 100, 0, -100 },
				{ 50, 0, -100 },
				{ -50, 0, -100 },
				{ -100, 0, -100 }
			}
	};
	bezPatch = new BezierPatch(controlPoints);
	// make Bezier surface shiny (temporary - just to test the lighting)
	Material bezMat = Material(diffuseMat, specularMat, emptyMat, 10.0, GL_FRONT_AND_BACK, white);
	bezPatch->setMaterial(bezMat);

	// Used for rendering Bezier patch wireframe
	glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, 4, 0, 1, 12, 4, &controlPoints[0][0][0]);
	glEnable(GL_MAP2_VERTEX_3);
	glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);

	glutMainLoop();

	return 0;
}
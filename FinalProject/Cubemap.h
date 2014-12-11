#pragma once
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include "GL\glut.h"


using namespace std;

class Cubemap {
private:
	string m_fileNames[6];
	GLuint skybox[6];

	GLuint vbo, vao;


public:
	Cubemap(
		const char* posXFilename,
		const char* negXFilename,
		const char* posYFilename,
		const char* negYFilename,
		const char* posZFilename,
		const char* negZFilename,
		int width, int height);
	~Cubemap();

	bool load();

	void createCubeMap(const char* front, const char* back, const char* top, const char* bottom, const char* left, const char* right, GLuint* tex_cube, int width, int height);
	void loadSide(GLuint texture, GLenum side_target, const char* file, int width, int height);
	void bind(GLenum textureUnit);

	GLuint getSkybox(int i) { return skybox[i]; }

	void render();
};


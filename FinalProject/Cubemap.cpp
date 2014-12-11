#ifdef _WIN32
#define _CRT_SECURE_NO_DEPRECATE
#endif

#include "Shader.h"
#include "Cubemap.h"
#include <iostream>

Cubemap::Cubemap(
	const char* posXFilename,
	const char* negXFilename,
	const char* posYFilename,
	const char* negYFilename,
	const char* posZFilename,
	const char* negZFilename,
	int width, int height) {
	float points[] = {
		-10.0f, 10.0f, -10.0f,
		-10.0f, -10.0f, -10.0f,
		10.0f, -10.0f, -10.0f,
		10.0f, -10.0f, -10.0f,
		10.0f, 10.0f, -10.0f,
		-10.0f, 10.0f, -10.0f,

		-10.0f, -10.0f, 10.0f,
		-10.0f, -10.0f, -10.0f,
		-10.0f, 10.0f, -10.0f,
		-10.0f, 10.0f, -10.0f,
		-10.0f, 10.0f, 10.0f,
		-10.0f, -10.0f, 10.0f,

		10.0f, -10.0f, -10.0f,
		10.0f, -10.0f, 10.0f,
		10.0f, 10.0f, 10.0f,
		10.0f, 10.0f, 10.0f,
		10.0f, 10.0f, -10.0f,
		10.0f, -10.0f, -10.0f,

		-10.0f, -10.0f, 10.0f,
		-10.0f, 10.0f, 10.0f,
		10.0f, 10.0f, 10.0f,
		10.0f, 10.0f, 10.0f,
		10.0f, -10.0f, 10.0f,
		-10.0f, -10.0f, 10.0f,

		-10.0f, 10.0f, -10.0f,
		10.0f, 10.0f, -10.0f,
		10.0f, 10.0f, 10.0f,
		10.0f, 10.0f, 10.0f,
		-10.0f, 10.0f, 10.0f,
		-10.0f, 10.0f, -10.0f,

		-10.0f, -10.0f, -10.0f,
		-10.0f, -10.0f, 10.0f,
		10.0f, -10.0f, -10.0f,
		10.0f, -10.0f, -10.0f,
		-10.0f, -10.0f, 10.0f,
		10.0f, -10.0f, 10.0f
	};
	
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 3 * 36 * sizeof(float), &points, GL_STATIC_DRAW);
	
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	createCubeMap(negZFilename, posZFilename, posYFilename, negYFilename, negXFilename, posXFilename, skybox, width, height);
}


Cubemap::~Cubemap() {
}

void Cubemap::createCubeMap(const char* front, const char* back, const char* top, const char* bottom, const char* left, const char* right, GLuint* tex_cube, int width, int height) {
	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, tex_cube);
	loadSide(*tex_cube, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, front, width, height);
	loadSide(*tex_cube, GL_TEXTURE_CUBE_MAP_POSITIVE_Z, back, width, height);
	loadSide(*tex_cube, GL_TEXTURE_CUBE_MAP_POSITIVE_Y, top, width, height);
	loadSide(*tex_cube, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, bottom, width, height);
	loadSide(*tex_cube, GL_TEXTURE_CUBE_MAP_NEGATIVE_X, left, width, height);
	loadSide(*tex_cube, GL_TEXTURE_CUBE_MAP_POSITIVE_X, right, width, height);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	// format cube map texture
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

void Cubemap::loadSide(GLuint texture, GLenum side_target, const char* filename, int width, int height) {
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
	int force_channels = 4;
	
	unsigned char *data;
	FILE *file;

	// open texture data
	file = fopen(filename, "rb");
	if (file == NULL) {
		printf("Error reading from file \"%s\". Please ensure it exists and try again.\n", filename);
		cin.get();
		exit(1);
	}
	// allocate buffer
	data = (unsigned char*)malloc(width * height * 4);

	// read texture data
	fread(data, width * height * 4, 1, file);
	fclose(file);

	// copy image data into 'target' side of cube map
	glTexImage2D(
		side_target,
		0,
		GL_RGB,
		width,
		height,
		0,
		GL_RGB,
		GL_UNSIGNED_BYTE,
		data
		);
	free(data);
}

void Cubemap::render() {
	glPushMatrix();
	//glLoadIdentity();

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_BLEND);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, skybox[0]);

	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glDepthMask(GL_TRUE);

	// Restore enable bits and matrix
	glDisable(GL_TEXTURE_2D);
	glPopAttrib();
	glPopMatrix();
}
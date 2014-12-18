#ifdef _WIN32
#define _CRT_SECURE_NO_DEPRECATE
#endif

#include "Shader.h"
#include "RoadGrid.h"
#include <iostream>

RoadGrid::RoadGrid(){
	loadTexture();
	srand(time(NULL));

	randomWidth = 2;
	for (int i = 0; i < 100; i++){
		randomHeight = rand() % 40;
		randomHeights[i] = randomHeight;
	}
	
	// load road textures
	/*loadRawTexture(texture[0], "../res/textures/road.raw", 512, 512);
	loadRawTexture(texture[1], "../res/textures/roadEmpty.raw", 512, 512);
	loadRawTexture(texture[2], "../res/textures/roadT.raw", 512, 512);
	loadRawTexture(texture[3], "../res/textures/roadTurn.raw", 512, 512);
	loadRawTexture(texture[4], "../res/textures/roadX.raw", 512, 512);*/

	int roadSize = 1;
	// create buildings
	for (int j = 0; j < 3; j++){
		for (int i = 0; i < 3; i++){
			/*tester->renderSkyscrapper(randomWidth, randomHeights[0 + i], (roadSize + randomWidth) + 7 * i, -3.0);
			tester->renderSkyscrapper(randomWidth, randomHeights[1 + i], (roadSize + randomWidth) + 7 * i, -10.0);
			tester->renderSkyscrapper(randomWidth, randomHeights[2 + i], (roadSize + randomWidth) + 7 * i, -17.0);*/
			buildings.push_back(new Building((roadSize + randomWidth) + 7 * i, randomHeights[0 + i] / 2, -3.0, randomWidth, randomHeights[0 + i], randomWidth));
			buildings.push_back(new Building((roadSize + randomWidth) + 7 * i, randomHeights[1 + i] / 2, -10.0, randomWidth, randomHeights[1 + i], randomWidth));
			buildings.push_back(new Building((roadSize + randomWidth) + 7 * i, randomHeights[2 + i] / 2, -17.0, randomWidth, randomHeights[2 + i], randomWidth));

		}
	}
}

void RoadGrid::render(int pid){

	float roadSize = 4;
	float spacing = 10;
	createGrid(roadSize, spacing, pid);

}

RoadGrid::~RoadGrid(){
	for (auto it = buildings.begin(); it != buildings.end(); ++it) {
		delete *it;
	}
	buildings.clear();
}

float RoadGrid::createRandomWidth(int maxWidth){
	float buildingWidth = rand() % maxWidth;
	return buildingWidth;
}

float RoadGrid::createRandomHeight(int maxHeight){
	
	float buildingHeight = rand() % maxHeight;
	return buildingHeight;
}


void RoadGrid::createGrid(float roadSize, float spacing, int shaderPid){
	/*************************************************
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);

	//glUniform1i(glGetUniformLocation(shaderPid, "tex"), 0);
	//GLint location = glGetUniformLocation(shaderPid, "tex");
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	//glActiveTexture(GL_TEXTURE1);
	//glBindTexture(GL_TEXTURE_2D, texture[0]);
	//glUniform1i(location, 0

	// check for errors
	
	//glBindTexture(GL_TEXTURE_2D, texture[0]);

	for (int j = -100; j < 120; j += spacing){
		for (int i = -100; i < 100; i += 2){
			
			//Builds the road forward
			//glActiveTexture(GL_TEXTURE0);
			
			//glUniform1i(glGetUniformLocationARB(shaderPid, "tex"), 0);
			glBindTexture(GL_TEXTURE_2D, texture[0]);
			//glActiveTexture(texture[0]);
			//glUniform1f(road, 20);
			glBegin(GL_QUADS);
				glTexCoord2f(0, 1); glVertex3f((-1.0 + i),0.1, -roadSize + j);
				glTexCoord2f(1, 1); glVertex3f((1.0 + i), 0.1, -roadSize + j);
				glTexCoord2f(1, 0); glVertex3f((1.0 + i), 0.1, roadSize + j);
				glTexCoord2f(0, 0); glVertex3f((-1.0 + i), 0.1, roadSize + j);
			glEnd();

			//Draw the roads laterally
			glBindTexture(GL_TEXTURE_2D, texture[4]);
			glBegin(GL_QUADS);
				//glColor3f(1.0, 1.0, 1.0);
				//glNormal3f(0.0, -1.0, 0.0);
				glTexCoord2f(0, 1); glVertex3f((-roadSize - j), 0.1, -1.0 + i);
				glTexCoord2f(1, 1); glVertex3f((roadSize - j), 0.1, -1.0 + i);
				glTexCoord2f(1, 0); glVertex3f((roadSize - j), 0.1, 1.0 + i);
				glTexCoord2f(0, 0); glVertex3f((-roadSize - j), 0.1, 1.0 + i);
			glEnd();
		}
	}
	glDisable(GL_TEXTURE_2D);
	createCity(roadSize);
	
	glPopMatrix();
	*************************************************/

	//Creates the roads that runs lenght wise
	
	glEnable(GL_TEXTURE_2D);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 512, 512, 0, GL_RGB, GL_UNSIGNED_BYTE, regRoad);
	glDisable(GL_BLEND);
	for (int i = int(-spacing / 2)*roadSize; i < int(spacing / 2)*roadSize + spacing; i += spacing){
		for (int j = int((-99) / roadSize); j < int(100 / roadSize); j += 2){
			glBegin(GL_QUADS);
			glNormal3f(0.0, 1.0, 0.0);
			if (i != j){
				glTexCoord2f(0, 1); glVertex3f(roadSize*(-1.0 + j), 0.1, roadSize*(-1.0 + i));
				glTexCoord2f(1, 1); glVertex3f(roadSize*(1.0 + j), 0.1, roadSize*(-1.0 + i));
				glTexCoord2f(1, 0); glVertex3f(roadSize*(1.0 + j), 0.1, roadSize*(1.0 + i));
				glTexCoord2f(0, 0); glVertex3f(roadSize*(-1.0 + j), 0.1, roadSize*(1.0 + i));
			}
			glEnd();
		}
	}
	glDisable(GL_TEXTURE_2D);


	//Creates the roads that runs latterally
	glEnable(GL_TEXTURE_2D);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 512, 512, 0, GL_RGB, GL_UNSIGNED_BYTE, regRoad);
	glDisable(GL_BLEND);
	for (int i = int(-spacing / 2)*roadSize; i < int(spacing / 2)*roadSize + spacing; i += spacing){
		for (int j = int((-99) / roadSize); j < int(100 / roadSize); j += 2){
			glBegin(GL_QUADS);
			glNormal3f(0.0, 1.0, 0.0);
			if (i != j){
				glTexCoord2f(1, 0); glVertex3f(roadSize*(-1.0 + i), 0.1, roadSize*(-1.0 + j));
				glTexCoord2f(1, 1); glVertex3f(roadSize*(1.0 + i), 0.1, roadSize*(-1.0 + j));
				glTexCoord2f(0, 1); glVertex3f(roadSize*(1.0 + i), 0.1, roadSize*(1.0 + j));
				glTexCoord2f(0, 0); glVertex3f(roadSize*(-1.0 + i), 0.1, roadSize*(1.0 + j));
			}
			glEnd();
		}
	}
	glDisable(GL_TEXTURE_2D);


	//Render the intersections
	glEnable(GL_TEXTURE_2D);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 512, 512, 0, GL_RGB, GL_UNSIGNED_BYTE, roadX);
	glDisable(GL_BLEND);
	for (int i = int(-spacing / 2)*roadSize; i < int(spacing / 2)*roadSize + spacing; i += spacing){
		for (int j = int((-99) / roadSize); j < int(100 / roadSize); j += 2){
			glBegin(GL_QUADS);
			glNormal3f(0.0, 1.0, 0.0);
			if (i != j){
				glTexCoord2f(1, 0); glVertex3f(roadSize*(-1.0 + i), 0.1, roadSize*(-1.0 + j));
				glTexCoord2f(1, 1); glVertex3f(roadSize*(1.0 + i), 0.1, roadSize*(-1.0 + j));
				glTexCoord2f(0, 1); glVertex3f(roadSize*(1.0 + i), 0.1, roadSize*(1.0 + j));
				glTexCoord2f(0, 0); glVertex3f(roadSize*(-1.0 + i), 0.1, roadSize*(1.0 + j));
			}
			glEnd();
		}
	}
	glDisable(GL_TEXTURE_2D);

	createCity(roadSize);
}

void RoadGrid::createCity(float roadSize){
	
	//Render a skyscrapper
	/*for (int j = 0; j < 3; j++){
		for (int i = 0; i < 3; i++){
			tester->renderSkyscrapper(randomWidth, randomHeights[0 + i], (roadSize + randomWidth) + 7 * i, -3.0);
			tester->renderSkyscrapper(randomWidth, randomHeights[1 + i], (roadSize + randomWidth) + 7 * i, -10.0);
			tester->renderSkyscrapper(randomWidth, randomHeights[2 + i], (roadSize + randomWidth) + 7 * i, -17.0);
		}
	}*/
	for (auto it = buildings.begin(); it != buildings.end(); ++it) {
		(*it)->render();
	}



}



unsigned char* loadPPM(const char* filename, int width, int height){

	const int BUFSIZE = 128;
	FILE* fp;
	unsigned int read;
	unsigned char* rawData;
	char buf[3][BUFSIZE];
	char* retval_fgets;
	size_t retval_sscanf;

	if ((fp = fopen(filename, "rb")) == NULL){
		std::cerr << "error reading ppm file, could not locate " << filename << std::endl;
		width = 0;
		height = 0;
		return NULL;
	}

	// Read magic number:
	retval_fgets = fgets(buf[0], BUFSIZE, fp);

	/*Removed because it breaks everything*/


	// Read width and height:
	//do{
	//	retval_fgets = fgets(buf[0], BUFSIZE, fp);
	//} while (buf[0][0] == '#');
	//retval_sscanf = sscanf(buf[0], "%s %s", buf[1], buf[2]);
	//width = atoi(buf[1]);
	//height = atoi(buf[2]);

	// Read maxval:
	do{
		retval_fgets = fgets(buf[0], BUFSIZE, fp);
	} while (buf[0][0] == '#');

	// Read image data:
	rawData = new unsigned char[width * height * 3];
	read = fread(rawData, width * height * 3, 1, fp);
	fclose(fp);

	if (read != 1){
		std::cerr << "error parsing ppm file, incomplete data" << std::endl;
		delete[] rawData;
		width = 0;
		height = 0;
		return NULL;
	}

	return rawData;
}



void RoadGrid::loadTexture(){

	// Load image file
	regRoad = loadPPM("../res/textures/regRoad.ppm", 512, 512);
	regRoadRotated = loadPPM("../res/textures/regRoad.ppm", 512, 512);
	road = loadPPM("../res/textures/road.ppm", 512, 512);
	roadEmpty = loadPPM("../res/textures/roadEmpty.ppm", 512, 512);
	roadT = loadPPM("../res/textures/roadT.ppm", 512, 512);
	roadTurn = loadPPM("../res/textures/roadTurn.ppm", 512, 512);
	roadTurnLarge = loadPPM("../res/textures/roadTurnLarge.ppm", 512, 512);
	roadX = loadPPM("../res/textures/roadX.ppm", 512, 512);

	//Check to make sure the textures existed
	if (road == NULL) return;
	if (roadEmpty == NULL) return;
	if (roadT == NULL) return;
	if (roadTurn == NULL) return;
	if (roadTurnLarge == NULL) return;
	if (roadX == NULL) return;

	// Create ID for texture
	glGenTextures(1, &texture[0]);

	// Set this texture to be the one we are working with
	glBindTexture(GL_TEXTURE_2D, texture[0]);

	// Make sure no bytes are padded:
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// Select GL_MODULATE to mix texture with polygon color for shading:
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	// Set bi-linear filtering for both minification and magnification
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (glGetError() != GL_NO_ERROR)
		std::cerr << gluErrorString(glGetError()) << std::endl;

	//glTexImage2D(GL_TEXTURE_2D, 0, 3, twidth, theight, 0, GL_RGB, GL_UNSIGNED_BYTE, tdata1);

}

void RoadGrid::loadRawTexture(GLuint texture,const char* filename, int width, int height) {
	
	//GLuint texture;
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
	
	//glActiveTexture(GL_TEXTURE1);
	// allocate a texture name
	glGenTextures(1, &texture);
	
	// select current texture
	//glBindTexture(GL_TEXTURE_2D, texture);

	// Make sure no bytes are padded
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// Select GL_MODULATE to mix texture with polygon color for shading
	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	// select modulate to mix texture with color for shading
	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_DECAL);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_DECAL);

	// when texture area is small, bilinear filter the closest mipmap
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	// when texture area is large, bilinear filter the first mipmap
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// texture should tile
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	//glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);

	// build our texture mipmaps
	gluBuild2DMipmaps(GL_TEXTURE_2D, 4, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);

	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	// free buffer
	free(data);

	// check for errors
	if (glGetError() != GL_NO_ERROR) cerr << gluErrorString(glGetError()) << endl;
	

	//return texture;
}
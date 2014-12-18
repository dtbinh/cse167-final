#include "CreateSkyscrapper.h"

CreateSkyscrapper::CreateSkyscrapper(){}

CreateSkyscrapper::~CreateSkyscrapper(){}

void CreateSkyscrapper::renderSkyscrapper(float width, float height, float xCoord, float zCoord){

	glEnable(GL_TEXTURE_2D);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 512, 512, 0, GL_RGB, GL_UNSIGNED_BYTE, windows);
	glDisable(GL_BLEND);
	glBegin(GL_QUADS);

	//glColor3f(0.0, 0.0, 1.0);

	glNormal3f(0.0, 0.0, 1.0);
	glTexCoord2f(1, 0); glVertex3f((-1.0 * width) + xCoord, 1.0 + height, (1.0 * width) + zCoord);
	glTexCoord2f(1, 1); glVertex3f((1.0 * width) + xCoord, 1.0 + height, (1.0 * width) + zCoord);
	glTexCoord2f(0, 1); glVertex3f((1.0 * width) + xCoord, -0.9, (1.0 * width) + zCoord);
	glTexCoord2f(0, 0); glVertex3f((-1.0 * width) + xCoord, -0.9, (1.0 * width) + zCoord);

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
	glDisable(GL_TEXTURE_2D);

}

unsigned char* loadPPMs(const char* filename, int width, int height){

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



void CreateSkyscrapper::loadTexture(){

	// Load image file

	//Check to make sure the textures existed
	if (windows == NULL) return;


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
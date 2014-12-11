#include "Material.h"

using namespace std;

Material::Material() {
}

Material::Material(GLfloat* d, GLfloat* s, GLfloat* a, GLfloat sh, GLenum frontback, GLfloat* c) {
	for (int i = 0; i < 4; ++i) {
		diffuse[i] = d[i];
		specular[i] = s[i];
		ambient[i] = a[i];
		if (i != 3) color[i] = c[i];
	}
	shininess = sh;
	fb = frontback;
}

Material::Material(const Material& m) {
	for (int i = 0; i < 4; ++i) {
		diffuse[i] = m.diffuse[i];
		specular[i] = m.specular[i];
		ambient[i] = m.ambient[i];
		if (i != 3) color[i] = m.color[i];
	}
	shininess = m.shininess;
	fb = m.fb;
}

Material::~Material() {
}

void Material::apply() {
	glMaterialfv(fb, GL_DIFFUSE, diffuse);
	glMaterialfv(fb, GL_SPECULAR, specular);
	glMaterialfv(fb, GL_AMBIENT, ambient);
	glMaterialf(fb, GL_SHININESS, shininess);
}

Material& Material::operator=(const Material& m) {
	for (int i = 0; i < 4; ++i) {
		diffuse[i] = m.diffuse[i];
		specular[i] = m.specular[i];
		ambient[i] = m.ambient[i];
		if (i != 3) color[i] = m.color[i];
	}
	shininess = m.shininess;
	fb = m.fb;

	return *this;
}
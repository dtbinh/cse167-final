#include "Light.h"


Light::Light(int l, GLfloat* d, GLfloat* s, GLfloat* a) : lightNum(l) {
	// set GL_LIGHT
	switch (l) {
	case 0: glLight = GL_LIGHT0; break;
	case 1: glLight = GL_LIGHT1; break;
	case 2: glLight = GL_LIGHT2; break;
	case 3: glLight = GL_LIGHT3; break;
	case 4: glLight = GL_LIGHT4; break;
	case 5: glLight = GL_LIGHT5; break;
	case 6: glLight = GL_LIGHT6; break;
	case 7: glLight = GL_LIGHT7; break;
	default: glLight = GL_LIGHT0; break;
	}

	for (int i = 0; i < 4; ++i) {
		diffuse[i] = d[i];
		specular[i] = s[i];
		ambient[i] = a[i];
	}
}


Light::~Light() {
}

void Light::enable() {
	setVisible(true);
	glEnable(glLight);
	glLightfv(glLight, GL_DIFFUSE, diffuse);
	glLightfv(glLight, GL_SPECULAR, specular);
	glLightfv(glLight, GL_AMBIENT, ambient);
}

void Light::setDiffuse(GLfloat *a) {
	for (int i = 0; i < 4; ++i) {
		diffuse[i] = a[i];
	}
	glLightfv(glLight, GL_DIFFUSE, diffuse);
}
void Light::setSpecular(GLfloat *a) {
	for (int i = 0; i < 4; ++i) {
		specular[i] = a[i];
	}
	glLightfv(glLight, GL_SPECULAR, specular);
}
void Light::setAmbient(GLfloat *a) {
	for (int i = 0; i < 4; ++i) {
		ambient[i] = a[i];
	}
	glLightfv(glLight, GL_AMBIENT, ambient);
}

//void Light::draw(Matrix4& m) {
//	glPushMatrix();
//	glMultMatrixd(m.getPointer());
//	glPopMatrix();
//}


PointLight::PointLight(int i, GLfloat* d, GLfloat *s, GLfloat *a, GLfloat* p) : Light(i, d, s, a) {
	for (int i = 0; i < 4; ++i) {
		pos[i] = p[i];
	}
	//enable();

}

void PointLight::enable() {
	glPushMatrix();
	setVisible(true);
	glEnable(glLight);
	glLightfv(glLight, GL_POSITION, pos);
	glLightfv(glLight, GL_DIFFUSE, diffuse);
	glLightfv(glLight, GL_SPECULAR, specular);
	glLightfv(glLight, GL_AMBIENT, ambient);
	glPopMatrix();
}

void PointLight::disable() {
	setVisible(false);
	glDisable(glLight);
	GLfloat black[] = { 0, 0, 0, 0 };
	glLightfv(glLight, GL_DIFFUSE, black);
	glLightfv(glLight, GL_SPECULAR, black);
}

PointLight::~PointLight() {

}

void PointLight::draw() {
	if (isVisible()) {
		glPushMatrix();
		//glLoadIdentity();
		glColor3f(1.0, 1.0, 1.0);
		//setPos(pos);
		glTranslated(pos[0], pos[1], pos[2]);
		glScaled(0.5, 0.5, 0.5);
		glutSolidSphere(5.0, 15, 15);
		glPopMatrix();
	}
}

void PointLight::setPosition(GLfloat *p) {
	for (int i = 0; i < 4; ++i)
		pos[i] = p[i];
}


SpotLight::SpotLight(int i, GLfloat* d, GLfloat *s, GLfloat *a, GLfloat *p, GLfloat *di, GLfloat e, GLfloat c) : Light(i, d, s, a) {
	for (int i = 0; i < 4; ++i) {
		pos[i] = p[i];
	}
	for (int i = 0; i < 3; ++i) {
		dir[i] = di[i];
	}
	exp = e;
	cutoff = c;
	enable();

}

SpotLight::~SpotLight() {

}

void SpotLight::enable() {
	setVisible(true);
	glEnable(glLight);
	glLightfv(glLight, GL_DIFFUSE, diffuse);
	glLightfv(glLight, GL_SPECULAR, specular);
	glLightfv(glLight, GL_AMBIENT, ambient);
	glLightfv(glLight, GL_POSITION, pos);

	glLightfv(glLight, GL_SPOT_DIRECTION, dir);
	glLightf(glLight, GL_SPOT_EXPONENT, exp);
	glLightf(glLight, GL_SPOT_CUTOFF, cutoff);
}

void SpotLight::disable() {
	setVisible(false);
	glDisable(glLight);
	GLfloat black[] = { 0, 0, 0, 0 };
	glLightfv(glLight, GL_DIFFUSE, black);
	glLightfv(glLight, GL_SPECULAR, black);
}

void SpotLight::draw() {
	if (isVisible()) {
		glPushMatrix();
		glLoadIdentity();
		//Vector3 vWorldPos = Vector3(0,0,1);
		//Vector3 directionVector = Vector3(dir[0], dir[1], dir[2]);
		//double angle = directionVector.angleFrom(vWorldPos);
		glColor3f(10.0, 10.0, 10.0);
		//Vector3 crossV;
		//crossV.cross(directionVector, vWorldPos);

		//glRotated(-90.0, 1.0, 0.0, 0.0);
		//setPos(pos);
		glTranslated(pos[0], pos[1], pos[2]);
		glRotated(angle, -1, 0, 0);
		glutSolidCone(1.0, 5.0, 10, 10);
		glPopMatrix();
	}

}

void SpotLight::setPosition(GLfloat *p) {
	for (int i = 0; i < 4; ++i)
		pos[i] = p[i];
}

void SpotLight::setDirection(GLfloat *d) {
	for (int i = 0; i < 3; ++i)
		dir[i] = d[i];
}
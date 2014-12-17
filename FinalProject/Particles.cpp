#include "Particles.h"


Particles::Particles(){
	
	this->InitParticles();
}
Particles::~Particles(){}


void Particles::InitParticles(){
	
	//Create Random timer
	srand(time(NULL));

	//loop throught particles and set target speed and
	//set to inavtive
	for(int p = 0; p < MAX_PARTICLES; p++){
		Part[p].Active =false;
		Part[p].tX = 0.0f;
		Part[p].tY = -0.1f;
		Part[p].tZ = 0.0f;
	}

}


void Particles::RenderParticles(){
	glBegin(GL_POINTS);
	for (int p = 0; p<MAX_PARTICLES; p++){
		if (Part[p].Active){
			glColor4f(1.0f, 0.0f, 0.0f, 0.5f);
			glVertex3f(Part[p].X, Part[p].Y, Part[p].Z);
		}
	}
	glEnd();
}

void Particles::ActivateParticles(){

	for (int p = 0; p < MAX_PARTICLES; p++){
		if (!Part[p].Active){
			//Start Particles at origin
			Part[p].X = 10.0f;
			Part[p].Y = 10.0f;
			Part[p].Z = 30.0f;
		
			//Set a random seed value
			Part[p].sX = (((float)((rand() % 100) + 1)) / 1000.0f) - 0.05f;
			Part[p].sY = (((float)((rand() % 100) + 50)) / 500.0f);
			Part[p].sZ = (((float)((rand() % 100) + 1)) / 1000.0f)	- 0.05f;

			// We also activate the particle
			Part[p].Active = true;

			//Set age to 0
			Part[p].Age = 0;
		
			//Set the max age of the particles
			Part[p].MaxAge = MAX_PARTICLE_AGE;
		
			//Set bounce count to 0
			Part[p].BounceCount = 0;

			//Only one particle will be active per frame
			return;
		}
	}
}

void Particles::AdjustParticles(){

	//Move the speed toward the target speed by 1/20
	for (int p = 0; p < MAX_PARTICLES; p++){
		Part[p].sX += (Part[p].tX - Part[p].sX) / 20.0f;
		Part[p].sY += (Part[p].tY - Part[p].sY) / 20.0f;
		Part[p].sZ += (Part[p].tZ - Part[p].sZ) / 20.0f;

		//adjust the position of the particles by the new speed
		Part[p].X += Part[p].sX;
		Part[p].Y += Part[p].sY;
		Part[p].Z += Part[p].sZ;

		// Bounce code
		if(Part[p].Y < 0.0f){
			Part[p].Y = 0.0f;
			Part[p].sY = - Part[p].sY;
			Part[p].BounceCount++;
			if(Part[p].BounceCount > MAX_BOUNCE_COUNT){
				Part[p].Active =false;
			}
		}
		//Preform the age check
		Part[p].Age++;
		if(Part[p].Age > Part[p].MaxAge){
			Part[p].Active = false;
		}
	}
}





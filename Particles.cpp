
#include "Particles.h"
#include <gl/glut.h>
#include <random>
#include <time.h>


Particles::Particles(void) {}

Particles::~Particles(void) {}


/* Creation */
void Particles::createParticleCylinder(float centerX, float centerZ, float initialY, float radius)
{
	// Random seed
	srand((unsigned)time(0));

	// Parameters
	this->centerX = centerX;
	this->initialY = initialY;
	this->centerZ = centerZ;
	this->radius = radius;

	for (unsigned int i = 0; i < NUM_PARTICLES; i++) {
		// Particles starting position: randomly distributed in a circle with center in (centerX, initialY, centerZ)
		float radiusAngle = rand()%360;
		particles[i].x = centerX + radius*cos(radiusAngle);
		particles[i].y = initialY;
		particles[i].z = centerZ + radius*sin(radiusAngle);

		// Particles x and z movement: 0 (only y movement)
		particles[i].vx = 0.0f;
		particles[i].vz = 0.0f;

		// Particle y movement: random
		particles[i].vy = (float)(rand()%250 + 50)/100.0f;
	}
}


/* Update */
void Particles::update()
{
	for (unsigned int i = 0; i < NUM_PARTICLES; i++) {
		// Move the particle
		particles[i].x = particles[i].x + particles[i].vx;
		particles[i].y = particles[i].y + particles[i].vy;
		particles[i].z = particles[i].z + particles[i].vz;

		// TODO HARDCODED
		if (particles[i].y >= 10.0f) {
			float radiusAngle = rand()%360;
			particles[i].x = centerX + radius*cos(radiusAngle);
			particles[i].y = initialY;
			particles[i].z = centerZ + radius*sin(radiusAngle);
		}
	}
}


/* Render */
void Particles::render()
{
	for (unsigned int i = 0; i < NUM_PARTICLES; i++) {
		glPushMatrix();
			glColor3f(1.0f, 1.0f, 1.0f);
			glTranslatef(particles[i].x, particles[i].y, particles[i].z);

			//GLUquadricObj *q = gluNewQuadric();
			//gluSphere(q, 0.025, 2, 2);
			//gluDeleteQuadric(q);

			glBegin(GL_QUADS);
				glVertex3f(-0.025f, 0.0f, -0.025f);
				glVertex3f(0.025f, 0.0f, -0.025f);
				glVertex3f(0.025f, 0.0f, 0.025f);
				glVertex3f(-0.025f, 0.0f, 0.025f);
			glEnd();

		glPopMatrix();
	}
}
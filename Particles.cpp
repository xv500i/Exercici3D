
#include "Particles.h"
#include <gl/glut.h>
#include <random>
#include <time.h>


Particles::Particles(void) {}

Particles::~Particles(void) {}


/* Creation */
void Particles::createParticleCylinder(float centerX, float centerZ, float initialY, float radius, std::vector<int> textures, std::vector<int> masks)
{
	// Display list
	createParticle();

	// Random seed
	srand((unsigned)time(0));

	// Parameters
	this->centerX = centerX;
	this->initialY = initialY;
	this->centerZ = centerZ;
	this->radius = radius;
	this->textures = textures;
	this->masks = masks;

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
		particles[i].vy = (float)(rand()%10)/100.0f;
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
void Particles::render(GameData &data)
{
	for (unsigned int i = 0; i < NUM_PARTICLES; i++) {
		int textureIndex = 0;
		if (textures.size() > 0) textureIndex = rand()%textures.size();
		else return;
		glEnable(GL_TEXTURE_2D);
		glPushMatrix();
			glColor3f(1.0f, 1.0f, 1.0f);
			glTranslatef(particles[i].x, particles[i].y, particles[i].z);

			glDisable(GL_DEPTH_TEST);
			glEnable(GL_BLEND);
			glBlendFunc(GL_DST_COLOR, GL_ZERO);
			glBindTexture(GL_TEXTURE_2D, data.getTextureID(masks[textureIndex]));
			glCallList(PARTICLE);

			glBlendFunc(GL_ONE, GL_ONE);
			glBindTexture(GL_TEXTURE_2D, data.getTextureID(textures[textureIndex]));
			glCallList(PARTICLE);
			glEnable(GL_DEPTH_TEST);
			glDisable(GL_BLEND);
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);
	}
}


/* Displaylist creation */
void Particles::createParticle()
{
	glNewList(PARTICLE, GL_COMPILE);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(0.0f, -0.2f, -0.2f);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(0.0f, 0.2f, -0.2f);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(0.0f, 0.2f, 0.2f);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(0.0f, -0.2f, 0.2f);
		glEnd();
	glEndList();
}
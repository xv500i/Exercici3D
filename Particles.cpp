
#include "Particles.h"
#include <gl/glut.h>
#include <random>
#include <time.h>
#include "Utility.h"


Particles::Particles(void) 
{
	createParticle();
}

Particles::~Particles(void) {}


/* Creation */
void Particles::createParticleCylinder(int numParticles, float centerX, float centerZ, float initialY, float finalY, float radius, float scale, std::vector<int> textures)
{
	// Random seed
	srand((unsigned)time(0));

	// Parameters
	this->numParticles = numParticles;
	this->centerX = centerX;
	this->centerZ = centerZ;
	this->initialY = initialY;
	this->finalY = finalY;
	this->radius = radius;
	this->scale = scale;
	this->textures = textures;
	particles = std::vector<Particle>(numParticles);

	for (int i = 0; i < numParticles; i++) {
		// Particles starting position: randomly distributed in a circle with center in (centerX, initialY, centerZ)
		float radiusAngle = rand()%360;
		particles[i].x = centerX + radius*cos(radiusAngle);
		particles[i].y = initialY;
		particles[i].z = centerZ + radius*sin(radiusAngle);

		// Particles x and z movement: 0 (only y movement)
		particles[i].vx = 0.0f;
		particles[i].vz = 0.0f;

		// Particle y movement: random
		particles[i].vy = (float)(rand()%90 + 10)/1000.0f;
	}
}

void Particles::createParticleExpansion(int numParticles, float centerX, float centerY, float centerZ, float distance, float scale, std::vector<int> textures)
{
	// Random seed
	srand((unsigned)time(0));

	// Parameters
	this->numParticles = numParticles;
	this->centerX = centerX;
	this->centerY = centerY;
	this->centerZ = centerZ;
	this->distance = distance;
	this->scale = scale;
	this->textures = textures;
	particles = std::vector<Particle>(numParticles);

	for (int i = 0; i < numParticles; i++) {
		// Particles starting position: center
		float radiusAngle = rand()%360;
		particles[i].x = centerX;
		particles[i].y = centerY;
		particles[i].z = centerZ;

		// Particles movement: random
		particles[i].vx = (float)(rand()%100 - 50)/100.0f;
		particles[i].vz = (float)(rand()%100 - 50)/100.0f;
		particles[i].vy = (float)(rand()%100 - 50)/100.0f;
	}
}


/* Update */
void Particles::updateParticleCylinder(float yAngle)
{
	this->yAngle = yAngle;

	for (int i = 0; i < numParticles; i++) {
		// Move the particle
		particles[i].x = particles[i].x + particles[i].vx;
		particles[i].y = particles[i].y + particles[i].vy;
		particles[i].z = particles[i].z + particles[i].vz;

		// Restart the particle
		if (particles[i].y > finalY) {
			float radiusAngle = rand()%360;
			particles[i].x = centerX + radius*cos(radiusAngle);
			particles[i].y = initialY;
			particles[i].z = centerZ + radius*sin(radiusAngle);
		}
	}
}

void Particles::updateParticleExpansion(float yAngle)
{
	this->yAngle = yAngle;

	for (int i = 0; i < numParticles; i++) {
		// Move the particle
		particles[i].x = particles[i].x + particles[i].vx;
		particles[i].y = particles[i].y + particles[i].vy;
		particles[i].z = particles[i].z + particles[i].vz;

		// Restart the particle
		if (distance3D(particles[i].x, particles[i].y, particles[i].z, centerX, centerY, centerZ) > distance) {
			particles[i].x = centerX;
			particles[i].y = centerY;
			particles[i].z = centerZ;
		}
	}
}


/* Render */
void Particles::render(GameData &data) const
{
	glEnable(GL_TEXTURE_2D);
	for (int i = 0; i < numParticles; i++) {
		int textureIndex = 0;
		if (textures.size() > 0) textureIndex = rand()%textures.size();
		else return;
		glPushMatrix();
			glColor3f(1.0f, 1.0f, 1.0f);
			glTranslatef(particles[i].x, particles[i].y, particles[i].z);
			glRotatef(-yAngle, 0.0f, 1.0f, 0.0f);
			glScalef(scale, scale, scale);

			glBindTexture(GL_TEXTURE_2D, data.getTextureID(textures[textureIndex]));
			glCallList(PARTICLE);
		glPopMatrix();
	}
	glDisable(GL_TEXTURE_2D);
}


/* Displaylist creation */
void Particles::createParticle()
{
	glNewList(PARTICLE, GL_COMPILE);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(0.0f, -1.0f, -1.0f);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(0.0f, 1.0f, -1.0f);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(0.0f, 1.0f, 1.0f);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(0.0f, -1.0f, 1.0f);
		glEnd();
	glEndList();
}
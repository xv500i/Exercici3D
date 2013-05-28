
#include "Particles.h"
#include <gl/glut.h>
#include <random>
#include <time.h>


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


/* Update */
void Particles::update(float yAngle)
{
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

		this->yAngle = yAngle;
	}
}


/* Render */
void Particles::render(GameData &data)
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
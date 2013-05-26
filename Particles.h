
#pragma once

#include <vector>


struct Particle {
	float x, y, z;		/* Particle initial position */
	float vx, vy, vz;	/* Particle velocity */
};


class Particles
{
private:
	const static int PARTICLE = 10;			// Displaylist identifier
	const static int NUM_PARTICLES = 200;

	Particle particles[NUM_PARTICLES];
	std::vector<int> textures;
	std::vector<int> masks;

	/* Particle cylinder */
	float centerX, initialY, centerZ;
	float radius;

	/* Displaylist creation */
	void createParticle();

public:
	Particles(void);
	virtual ~Particles(void);

	/* Creation */
	void createParticleCylinder(float centerX, float centerZ, float initialY, float radius, std::vector<int> textures, std::vector<int> masks);

	/* Update */
	void update();

	/* Render */
	void render();
};
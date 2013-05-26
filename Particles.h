
#pragma once


struct Particle {
	float x, y, z;		/* Particle initial position */
	float vx, vy, vz;	/* Particle velocity */
};


class Particles
{
private:
	const static int NUM_PARTICLES = 500;

	Particle particles[NUM_PARTICLES];

	/* Particle cylinder */
	float centerX, initialY, centerZ;
	float radius;

public:
	Particles(void);
	virtual ~Particles(void);

	/* Creation */
	void createParticleCylinder(float centerX, float centerZ, float initialY, float radius);

	/* Update */
	void update();

	/* Render */
	void render();
};
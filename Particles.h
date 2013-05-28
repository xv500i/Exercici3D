
#pragma once

#include <vector>
#include "GameData.h"


struct Particle {
	float x, y, z;		/* Particle initial position */
	float vx, vy, vz;	/* Particle velocity */
};


class Particles
{
private:
	const static int PARTICLE = 10;			// Displaylist identifier

	std::vector<Particle> particles;
	std::vector<int> textures;

	/* Particle cylinder */
	int numParticles;
	float centerX, centerZ;
	float initialY, finalY;
	float scale;
	float radius;
	float yAngle;

	/* Displaylist creation */
	void createParticle();

public:
	Particles(void);
	virtual ~Particles(void);

	/* Creation */
	void createParticleCylinder(int numParticles, float centerX, float centerZ, float initialY, float finalY, float radius, float scale, std::vector<int> textures);

	/* Update */
	void update(float yAngle);

	/* Render */
	void render(GameData &data);
};

#pragma once

#include <vector>
#include "GameData.h"


struct Particle {
	float x, y, z;		/* Particle initial position */
	float vx, vy, vz;	/* Particle velocity */
	bool active;		
};


class Particles
{
private:
	const static int PARTICLE = 10;			// Displaylist identifier

	std::vector<Particle> particles;
	std::vector<int> textures;

	/* Particle parameters */
	int numParticles;
	float centerX, centerY, centerZ;
	float initialY, finalY;
	float offsetX, offsetY, offsetZ;
	float distance;
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
	void createParticleExpansion(int numParticles, float centerX, float centerY, float centerZ, float distance, float scale, std::vector<int> textures);
	void createParticleCharging(int numParticles, float centerX, float centerY, float centerZ, float radius, float scale, std::vector<int> textures);

	/* Update */
	void updateParticleCylinder(float yAngle);
	void updateParticleExpansion(float yAngle, float offsetX, float offsetY, float offsetZ);
	void updateParticleCharging(float yAngle, float offsetX, float offsetY, float offsetZ);

	/* Render */
	void render(GameData &data) const;
};
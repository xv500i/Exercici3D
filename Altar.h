
#pragma once

#include "GameObject.h"
#include "Particles.h"


class Altar :
	public GameObject
{
private:
	bool active;

	/* Particle aura */
	Particles aura;
	bool particlesCreated;

public:
	Altar(void);
	virtual ~Altar(void);

	/* Update */
	void update(float visionYAngle);

	/* Render */
	void render(GameData &data);

	/* Altar activation */
	void activate();
	bool isActive();
};
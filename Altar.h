
#pragma once

#include "GameObject.h"
#include "Particles.h"


class Altar :
	public GameObject
{
private:
	const static int TICS_ACTIVE_LIMIT = 50;

	bool active;

	/* Particle aura */
	Particles aura;
	bool particlesCreated;
	int ticsActive;

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
	bool isActiveAndFinished();
};
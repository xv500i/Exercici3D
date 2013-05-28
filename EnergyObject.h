
#pragma once

#include "ItemObject.h"
#include "Particles.h"


class EnergyObject : public ItemObject
{
private:
	const static float Y_VELOCITY;

	/* Particle aura */
	Particles aura;
	bool particlesCreated;

	/* Y position */
	float offsetY;
	bool goingUp;

public:
	EnergyObject(void);
	virtual ~EnergyObject(void);

	/* Update */
	void update(float visionYAngle);

	/* Render */
	void render(GameData &data);
};


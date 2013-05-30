
#pragma once

#include "ItemObject.h"
#include "Particles.h"


class EnergyObject : public ItemObject
{
private:
	const static float VELOCITY_Y;
	const static float MIN_OFFSET_Y;
	const static float MAX_OFFSET_Y;

	/* Particle aura */
	Particles aura;
	bool particlesCreated;

	/* Y position */
	float offsetY;
	bool goingUp;
	bool playSpark;

public:
	EnergyObject(void);
	virtual ~EnergyObject(void);

	/* Update */
	void update(float visionYAngle);

	/* Render */
	void render(GameData &data);
};


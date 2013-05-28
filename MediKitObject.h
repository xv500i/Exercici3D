
#pragma once

#include "ItemObject.h"
#include "GameData.h"


class MediKitObject : public ItemObject
{
private:
	const static float INCREMENT_Y_ANGLE;

	float yAngle;
	bool yPositionUpdated;

public:
	MediKitObject(void);
	virtual ~MediKitObject(void);

	/* Update */
	void update();

	/* Render */
	void render(GameData &data);
};


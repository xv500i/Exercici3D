
#pragma once

#include "ItemObject.h"
#include "GameData.h"


class MediKitObject : public ItemObject
{
public:
	MediKitObject(void);
	virtual ~MediKitObject(void);

	/* Update */
	void update();

	/* Render */
	void render(GameData &data);
};


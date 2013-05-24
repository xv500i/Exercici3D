
#pragma once

#include "GameData.h"


class Landscape
{
private:
	float rotation;
	int textureIndex;

public:
	Landscape();
	Landscape(int textureIndex);
	virtual ~Landscape(void);

	/* Update */
	void update();

	/* Render */
	void render(GameData &data);
};


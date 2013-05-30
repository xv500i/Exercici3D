
#pragma once

#include "GameData.h"


class Landscape
{
private:
	const static int LANDSCAPE = 30;	// Displaylist identifier

	float rotation;
	int textureIndex;

	/* Displaylist creation */
	void createLandscape();

public:
	Landscape();
	Landscape(int textureIndex);
	virtual ~Landscape(void);

	/* Update */
	void update();

	/* Render */
	void render(GameData &data);
};



#pragma once

#include "GameData.h"


class HUDElement
{
private:
	int x, y;			// Position of the HUD element
	int width, height;	// Width and height of the HUD element
	int textureIndex;

public:
	HUDElement(void);
	HUDElement(int x, int y, int width, int height, int textureIndex);
	virtual ~HUDElement(void);

	/* Render */
	void render(GameData &data);

	/* Setters */
	void setTextureIndex(int newTextureIndex);
};


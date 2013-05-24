
#pragma once

#include <vector>
#include "HUDElement.h"


class HUD
{
private:
	const static int MAX_LIFE = 3;
	const static int LIFE_ELEMENT_SIZE = 32;
	const static int ITEM_ELEMENT_SIZE = 32;

	std::vector<HUDElement> playerLife;
	std::vector<HUDElement> playerItems;

public:
	HUD(void);
	~HUD(void);

	/* Loading */
	bool load(int screenWidth, int screenHeight);

	/* Updating */
	void update(int life);

	/* Rendering */
	void render(GameData &data, int screenWidth, int screenHeight);
};


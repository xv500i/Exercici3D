
#pragma once

#include <vector>
#include "HUDElement.h"


class HUD
{
private:
	const static int LIFE_ELEMENT_SIZE = 48;
	const static int ENERGY_ELEMENT_SIZE = 48;

	int screenWidth;
	int screenHeight;

	std::vector<HUDElement> playerLife;
	std::vector<HUDElement> playerEnergy;

public:
	HUD(void);
	~HUD(void);

	/* Loading */
	bool load(int screenWidth, int screenHeight, int maxLife);

	/* Updating */
	void update(int life, int energy);

	/* Rendering */
	void render(GameData &data);
};


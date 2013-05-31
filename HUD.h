
#pragma once

#include <vector>
#include "HUDElement.h"
#include "FusRoDahHUDElement.h"


class HUD
{
private:
	const static int LIFE_ELEMENT_SIZE = 48;
	const static int ENERGY_ELEMENT_SIZE = 48;
	const static int INSTRUCTIONS_ELEMENT_WIDTH = 220;
	const static int INSTRUCTIONS_ELEMENT_HEIGHT = 120;
	const static int FUSRODAH_ELEMENT_WIDTH = 240;
	const static int FUSRODAH_ELEMENT_HEIGHT = 36;
	const static int MARGIN_BETWEEN_ELEMENTS = 8;

	const static int TICS_CHANGE_INSTRUCTIONS = 200;

	int screenWidth;
	int screenHeight;

	// Instructions
	bool showInstr;
	int ticsInstr;

	std::vector<HUDElement> playerLife;
	std::vector<HUDElement> playerEnergy;
	HUDElement instructions;
	FusRoDahHUDElement fusRoDah;

public:
	HUD(void);
	~HUD(void);

	/* Loading */
	bool load(int screenWidth, int screenHeight, int maxLife);

	/* Updating */
	void update(int life, int energy, int ticsFusRoDah);

	/* Rendering */
	void render(GameData &data);

	/* Instructions */
	void showInstructions();
};


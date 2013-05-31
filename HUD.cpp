
#include "HUD.h"


HUD::HUD(void) 
{
	showInstr = false;
	ticsInstr = 0;
}

HUD::~HUD(void) {}


/* Loading */
bool HUD::load(int screenWidth, int screenHeight, int maxLife)
{
	this->screenWidth = screenWidth;
	this->screenHeight = screenHeight;

	// HUD Life
	playerLife = std::vector<HUDElement>(maxLife);
	for (int i = 0; i < maxLife; i++) {
		playerLife[i] = HUDElement(i*LIFE_ELEMENT_SIZE, 0, LIFE_ELEMENT_SIZE, LIFE_ELEMENT_SIZE, GameData::LIFEFULL_HUD_TEXTURE_INDEX);
	}

	// First instructions
	int x = screenWidth/2 - INSTRUCTIONS_ELEMENT_WIDTH/2;
	instructions = HUDElement(x, 0, INSTRUCTIONS_ELEMENT_WIDTH, INSTRUCTIONS_ELEMENT_HEIGHT, GameData::INSTRUCTIONS_HUD_MOVE_INDEX);
	
	// Fus-Ro-Dah
	fusRoDah = FusRoDahHUDElement(screenWidth - FUSRODAH_ELEMENT_WIDTH, 0, FUSRODAH_ELEMENT_WIDTH, FUSRODAH_ELEMENT_HEIGHT, GameData::FUSRODAH_HUD_TEXTURE_INDEX);

	return true;
}


/* Updating */
void HUD::update(int life, int energy, int ticsFusRoDah)
{
	// Player Life
	for (unsigned int i = 0; i < playerLife.size(); i++) {
		// Action
		if (life > (int)i) playerLife[i].setTextureIndex(GameData::LIFEFULL_HUD_TEXTURE_INDEX);
		else playerLife[i].setTextureIndex(GameData::LIFEEMPTY_HUD_TEXTURE_INDEX);	
	}

	// Player energy
	while ((int)playerEnergy.size() > energy) playerEnergy.pop_back();
	while ((int)playerEnergy.size() < energy) {
		HUDElement element = HUDElement(screenWidth - (playerEnergy.size() + 1)*ENERGY_ELEMENT_SIZE, FUSRODAH_ELEMENT_HEIGHT + MARGIN_BETWEEN_ELEMENTS, ENERGY_ELEMENT_SIZE, ENERGY_ELEMENT_SIZE, GameData::ENERGY_HUD_TEXTURE_INDEX);
		playerEnergy.push_back(element);
	}

	// Instructions
	if (showInstr) {
		ticsInstr++;
		if (ticsInstr == TICS_CHANGE_INSTRUCTIONS) {
			int x = screenWidth/2 - INSTRUCTIONS_ELEMENT_WIDTH/2;
			instructions = HUDElement(x, 0, INSTRUCTIONS_ELEMENT_WIDTH, INSTRUCTIONS_ELEMENT_HEIGHT, GameData::INSTRUCTIONS_HUD_ACTIONS_INDEX);
		}
		else if (ticsInstr == TICS_CHANGE_INSTRUCTIONS*2) {
			int x = screenWidth/2 - INSTRUCTIONS_ELEMENT_WIDTH/2;
			instructions = HUDElement(x, 0, INSTRUCTIONS_ELEMENT_WIDTH, INSTRUCTIONS_ELEMENT_HEIGHT, GameData::INSTRUCTIONS_HUD_WIN_INDEX);
		}
		else if (ticsInstr == TICS_CHANGE_INSTRUCTIONS*3) showInstr = false;
	}

	// Fus-Ro-Dah
	fusRoDah.update(ticsFusRoDah);
}


/* Rendering */
void HUD::render(GameData &data)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0f, screenWidth, screenHeight, 0.0f, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	for (unsigned int i = 0; i < playerLife.size(); i++) {
		playerLife[i].render(data);
	}
	for (unsigned int i = 0; i < playerEnergy.size(); i++) {
		playerEnergy[i].render(data);
	}
	fusRoDah.render(data);
	if (showInstr) instructions.render(data);
}


/* Instructions */
void HUD::showInstructions()
{
	showInstr = true;
	ticsInstr = 0;
}
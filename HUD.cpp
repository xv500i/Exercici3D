
#include "HUD.h"


HUD::HUD(void) {}

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
	return true;
}


/* Updating */
void HUD::update(int life, int energy)
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
		HUDElement element = HUDElement(screenWidth - (playerEnergy.size() + 1)*ENERGY_ELEMENT_SIZE, 0, ENERGY_ELEMENT_SIZE, ENERGY_ELEMENT_SIZE, GameData::ENERGY_HUD_TEXTURE_INDEX);
		playerEnergy.push_back(element);
	}
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
}
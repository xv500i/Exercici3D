
#include "HUD.h"


HUD::HUD(void) {}

HUD::~HUD(void) {}


/* Loading */
bool HUD::load(int screenWidth, int screenHeigth, int maxLife)
{
	// HUD Life
	playerLife = std::vector<HUDElement>(maxLife);
	for (int i = 0; i < maxLife; i++) {
		playerLife[i] = HUDElement(i*LIFE_ELEMENT_SIZE, 0, LIFE_ELEMENT_SIZE, LIFE_ELEMENT_SIZE, GameData::LIFEFULL_HUD_TEXTURE_INDEX);
	}
	return true;
}


/* Updating */
void HUD::update(int life)
{
	// Player Life
	for (unsigned int i = 0; i < playerLife.size(); i++) {
		// Action
		if (life > (int)i) playerLife[i].setTextureIndex(GameData::LIFEFULL_HUD_TEXTURE_INDEX);
		else playerLife[i].setTextureIndex(GameData::LIFEEMPTY_HUD_TEXTURE_INDEX);	
	}
}


/* Rendering */
void HUD::render(GameData &data, int screenWidth, int screenHeight)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0f, screenWidth, screenHeight, 0.0f, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	for (unsigned int i = 0; i < playerLife.size(); i++) {
		playerLife[i].render(data);
	}
}
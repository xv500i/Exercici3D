
#include "HUD.h"


HUD::HUD(void) {}

HUD::~HUD(void) {}


/* Loading */
bool HUD::load(int screenWidth, int screenHeigth)
{
	// HUD Life
	int x = 0;
	int y = 0;
	playerLife = std::vector<HUDElement>(MAX_LIFE);
	for (unsigned i = 0; i < MAX_LIFE; i++) {
		playerLife[i] = HUDElement(x + i*LIFE_ELEMENT_SIZE, y, LIFE_ELEMENT_SIZE, LIFE_ELEMENT_SIZE, GameData::LIFEFULL_HUD_TEXTURE_INDEX);
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
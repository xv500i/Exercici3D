#include "GameMenu.h"
#include "gl\glut.h"

GameMenu::GameMenu(void)
{
	currentOption = 0;
	selected = NONE_SELECTED;
	maxTicks = 25;
	currentTicks = maxTicks;
	interactionTicksMax = 18;
	currentInteractionTicks = interactionTicksMax;
}

GameMenu::~GameMenu(void)
{
}

void GameMenu::createGameOver()
{
	opts = std::vector<MenuOption>(2);
	opts[0] = TO_MAIN_MENU;
	opts[1] = QUIT_GAME;
	type = 'g';
}

void GameMenu::createCongrats()
{
	opts = std::vector<MenuOption>(2);
	opts[0] = TO_MAIN_MENU;
	opts[1] = QUIT_GAME;
	type = 'c';
}

void GameMenu::createLevelCompleted()
{
	opts = std::vector<MenuOption>(2);
	opts[0] = TO_NEXT_LEVEL;
	opts[1] = TO_MAIN_MENU;
	type = 'l';
}

void GameMenu::createMain()
{
	opts = std::vector<MenuOption>(3);
	opts[0] = START_GAME;
	opts[1] = SHOW_INSTRUCTIONS;
	opts[2] = QUIT_GAME;
	type = 'm';
}

void GameMenu::createPause()
{
	opts = std::vector<MenuOption>(3);
	opts[0] = RESTART_GAME;
	opts[1] = TO_MAIN_MENU;
	opts[2] = QUIT_GAME;
	type = 'p';
}

void GameMenu::createInstructions()
{
	opts = std::vector<MenuOption>(1);
	opts[0] = TO_MAIN_MENU;
	type = 'i';
}

void GameMenu::render(GameData &data)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 800, 0, 600, -3.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	int tex;
	switch(type) {
	case 'm':
		tex = GameData::TITLE_INDEX;
		break;
	case 'p':
		tex = GameData::PAUSE_INDEX;
		break;
	case 'i':
		tex = GameData::INSTRUCTIONS_INDEX;
		break;
	case 'g':
		tex = GameData::GAMEOVER_INDEX;
		break;
	case 'c':
		tex = GameData::CONGRATS_INDEX;
		break;
	case 'l':
		tex = GameData::LEVEL_COMPLETED_INDEX;
		break;
	}
	paint(data.getTextureID(tex), 400, 530, 450, 150);
	float xi = 400;
	float yi = 420.0f;
	float w = 200;
	float h = 50;
	float margin = 30.f;
	for (unsigned int i = 0; i < opts.size(); i++) {
		switch(opts[i]) {
		case RESTART_GAME:
			tex = GameData::RESTART_INDEX;
			break;
		case QUIT_GAME:
			tex = GameData::QUIT_INDEX;
			break;
		case TO_MAIN_MENU:
			tex = GameData::RETURN_INDEX;
			break;
		case START_GAME:
			tex = GameData::START_INDEX;
			break;
		case SHOW_INSTRUCTIONS:
			tex = GameData::HELP_TEX_INDEX;
			break;
		case TO_NEXT_LEVEL:
			tex = GameData::NEXT_LEVEL_INDEX;
			break;
		}
		paint(data.getTextureID(tex), xi, yi, w, h);
		yi -= (h + margin);
	}
	if (showCursor) {
		float cw = 100;
		float ch = 100;
		float cx = xi - w/2 - cw/2;
		float cy = 420.0f - currentOption*(h+margin);
		
		paint(data.getTextureID(GameData::CURSOR_INDEX), cx, cy, cw, ch);
	}
	if (type == 'i') {
		paint(data.getTextureID(GameData::MANUAL_INDEX), xi, yi - 2*(h + margin),  400, 400);
	}
	
}

void GameMenu::update()
{
	currentTicks--;
	if (currentTicks == 0) {
		showCursor = !showCursor;
		currentTicks = maxTicks;
	}
	selected = NONE_SELECTED;
	if (currentInteractionTicks > 0) currentInteractionTicks--;
}

void GameMenu::upPressed()
{
	if (currentInteractionTicks > 0) return;
	currentOption--;
	if (currentOption < 0) currentOption = opts.size() - 1;
	currentInteractionTicks = interactionTicksMax;
}

void GameMenu::downPressed()
{
	if (currentInteractionTicks > 0) return;
	currentOption++;
	if (currentOption >= (signed)opts.size()) currentOption = 0;
	currentInteractionTicks = interactionTicksMax;
}

void GameMenu::enterPressed()
{
	if (currentInteractionTicks > 0) return;
	selected = opts[currentOption];
	currentInteractionTicks = interactionTicksMax;
}

MenuOption GameMenu::getSelected()
{
	return selected;
}

void GameMenu::paint(int idTexture, float x, float y, float w, float h)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, idTexture);
	glPushMatrix();
	glTranslatef(x, y, 0.0f);
	glBegin(GL_QUADS);
		// Bottom-left
		glTexCoord2f(0, 1);
		glVertex3i(- w/2 , - h/2, 1);
		// Top-left
		glTexCoord2f(0, 0);
		glVertex3i(- w/2 , + h/2, 1);
		// Top-right
		glTexCoord2f(1, 0);
		glVertex3i(+ w/2 , + h/2, 1);
		// Bottom-right
		glTexCoord2f(1, 1);
		glVertex3i(+ w/2 , - h/2, 1);	
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}
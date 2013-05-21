
#include "MenuHandler.h"


MenuHandler::MenuHandler(void) : activeMenu(&mainMenu) {}

MenuHandler::~MenuHandler(void) {}


/* Menu creation */
void MenuHandler::createMenus()
{
	mainMenu.createMain();
	instructionsMenu.createInstructions();
	pauseMenu.createPause();
	gameOverMenu.createGameOver();
	congratsMenu.createCongrats();
	nextLevelMenu.createLevelCompleted();
}


/* Input */
void MenuHandler::resolveActiveMenuInput(InputHandler &input)
{
	// TODO: afegir tecles a inputHandler
	if (input.keyIsDown('s')) activeMenu->downPressed();
	else if (input.keyIsDown('w')) activeMenu->upPressed();
	else if (input.keyIsDown(' ')) activeMenu->enterPressed();
}


/* Update */
void MenuHandler::updateActiveMenu()
{
	activeMenu->update();
}


/* Render */
void MenuHandler::renderActiveMenu(GameData &data)
{
	activeMenu->render(data);
}


/* Getters */
MenuOption MenuHandler::getActiveMenuSelected()
{
	return activeMenu->getSelected();
}


/* Setters */
void MenuHandler::setActiveMenu(MenuType menuType)
{
	switch (menuType) {
	case MAIN:				activeMenu = &mainMenu; break;
	case PAUSE:				activeMenu = &pauseMenu; break;
	case INSTRUCTIONS:		activeMenu = &instructionsMenu; break;
	case GAME_OVER:			activeMenu = &gameOverMenu; break; 
	case NEXT_LEVEL:		activeMenu = &nextLevelMenu; break;
	case CONGRATULATIONS:	activeMenu = &congratsMenu; break;
	default: break;
	}
}
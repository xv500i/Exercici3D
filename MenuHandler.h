
#pragma once

#include "GameMenu.h"
#include "InputHandler.h"
#include "GameData.h"


enum MenuType {
	MAIN,
	PAUSE,
	INSTRUCTIONS,
	GAME_OVER,
	NEXT_LEVEL,
	CONGRATULATIONS
};


class MenuHandler
{
private:
	GameMenu mainMenu;			/* The main menu */
	GameMenu pauseMenu;			/* Pause menu */
	GameMenu instructionsMenu;	/* Menu with game instructions */
	GameMenu gameOverMenu;		/* Menu that appears when the player is killed */
	GameMenu nextLevelMenu;		/* Menu that appears at the end of the level */
	GameMenu congratsMenu;		/* Menu that appears when you win the game */

	GameMenu *activeMenu;		/* Pointer to the active menu */

public:
	MenuHandler(void);
	virtual ~MenuHandler(void);

	/* Menu creation */
	void createMenus();

	/* Input */
	void resolveActiveMenuInput(InputHandler &input);

	/* Update */
	void updateActiveMenu();

	/* Render */
	void renderActiveMenu(GameData &data);

	/* Getters */
	MenuOption getActiveMenuSelected();

	/* Setters */
	void setActiveMenu(MenuType menuType);
};


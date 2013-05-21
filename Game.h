
#pragma once

#include "InputHandler.h"
#include "CameraHandler.h"
#include "MenuHandler.h"
#include "Scene.h"
#include "GameState.h"
#include "GameMenu.h"


class Game
{
private:
	/* Game desired framerate */
	const static int FRAMERATE = 30;

	InputHandler input;		/* Input handler */
	MenuHandler menus;		/* Menu handler */
	CameraHandler camera;	/* Camera handler */
	GameData data;			/* Game data */
	GameState gameState;	/* Game state */
	Scene scene;			/* The scene */

	/* Game menus */
	/*GameMenu mainMenu;
	GameMenu instructionsMenu;
	GameMenu pauseMenu;
	GameMenu gameOverMenu;
	GameMenu congratsMenu;
	GameMenu nextLevelMenu;*/

	bool debug;

public:
	/* Game screen size */
	const static int SCREEN_WIDTH = 800;
	const static int SCREEN_HEIGHT = 600;

	Game(void);
	virtual ~Game(void);

	/* Game initialization */
	bool init();

	/* Game loop */
	bool loop();

	/* Game finalization */
	void finalize();
	
	/* Input */
	void readKeyboard(unsigned char key, int x, int y, bool press);
	void readMouse(int button, int state, int x, int y);
	
	/* Process */
	bool process();
	
	/* Render */
	void render();
	void encapsulateDrawing();
};
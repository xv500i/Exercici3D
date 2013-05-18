#pragma once

#include "Scene.h"
#include "InputHandler.h"
#include "CameraHandler.h"
#include "GameState.h"
#include "GameMenu.h"

#define SCREEN_WIDTH	800
#define SCREEN_HEIGHT	600

class Game
{
private:
	const static int FRAMERATE = 30;

	InputHandler input;
	CameraHandler camera;
	//FreeCamera camera;
	Scene Scene;
	GameData data;			/* Game data */
	bool debug;
	//int selectedCamera;
	
	GameState gameState;	/* Game state */

	/* Game menus */
	GameMenu mainMenu;
	GameMenu instructionsMenu;
	GameMenu pauseMenu;
	GameMenu gameOverMenu;
	GameMenu congratsMenu;
	GameMenu nextLevelMenu;

public:
	Game(void);
	virtual ~Game(void);

	bool init();
	bool loop();
	void finalize();
	//Input
	void readKeyboard(unsigned char key, int x, int y, bool press);
	void readMouse(int button, int state, int x, int y);
	//Process
	bool process();
	//Output
	void render();
	void encapsulateDrawing();
};

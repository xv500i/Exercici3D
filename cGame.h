#pragma once

#include "cScene.h"
//#include "cData.h"
#include "InputHandler.h"
#include "Camera.h"
#include "GameState.h"
#include "GameMenu.h"

#define SCREEN_WIDTH	800
#define SCREEN_HEIGHT	600

class cGame
{
private:
	InputHandler input;
	Camera camera;
	cScene Scene;
	//cData Data;
	GameData data;			/* Game data */
	bool debug;
	int selectedCamera;
	
	GameState gameState;	/* Game state */

	/* Game menus */
	GameMenu mainMenu;
	GameMenu instructionsMenu;
	GameMenu pauseMenu;
	GameMenu gameOverMenu;
	GameMenu congratsMenu;
	GameMenu nextLevelMenu;

public:
	cGame(void);
	virtual ~cGame(void);

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

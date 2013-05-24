
#include "Game.h"
#include "Globals.h"
#include <math.h>
#include <time.h>
#include <random>


Game::Game(void) {}
Game::~Game(void) {}


/* Game initialization */
bool Game::init()
{
	bool res = true;

	// Random seed
	srand((unsigned)time(0));
	
	//Graphics initialization
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (float)SCREEN_WIDTH/(float)SCREEN_HEIGHT, 0.1, 10000);
	glMatrixMode(GL_MODELVIEW);
	
	glEnable(GL_DEPTH_TEST);
	glAlphaFunc(GL_GREATER, 0.05f);
	glEnable(GL_ALPHA_TEST);

	// Data loading
	if (!data.loadTextures()) return false;
	if (!data.loadTileSheets()) return false;
	if (!data.loadSprites()) return false;
	if (!data.loadSounds()) return false;

	// Scene initialization
	scene.Init();

	// Menu creation
	menus.createMenus();
	
	gameState = MAIN_MENU;
	debug = true;
	data.playSound(GameData::INTRO_THEME_INDEX);

	return res;
}


/* Game loop */
bool Game::loop()
{
	int t1, t2;
	t1 = glutGet(GLUT_ELAPSED_TIME);

	bool b = process();
	if (b) render();
	do {
		t2 = glutGet(GLUT_ELAPSED_TIME);
	} while (t2 - t1 < 1000/FRAMERATE);

	if (!b) exit(0);
	return b;
}


/* Game finalization */
void Game::finalize() {}


/* Input */
void Game::readKeyboard(unsigned char key, int x, int y, bool press)
{
	input.setKeyState(key, press);
}

void Game::readMouse(int button, int state, int x, int y) 
{
	if (button == -1) input.setMousePosition(x, y);
	else input.setMouseButtonState(button, state);
}


/* Process */
bool Game::process()
{
	/* PLAYING */
	if (gameState == PLAYING) {
		if (input.keyIsDown(input.getKey(SHOW_PAUSE_MENU))) gameState = PAUSE_MENU;
		else {
			// Active camera
			camera.resolveInput(input);
			// Free camera
			if (camera.getActiveCamera() == FREE) camera.resolveFreeCameraInput(input);
			
			// Polygon Mode
			if (input.keyIsDown(input.getKey(WIREFRAME_MODE))) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);  
			else if (input.keyIsDown(input.getKey(FILL_MODE))) glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			
			// Scene update	
			if (input.keyIsDown('r')) scene.resetRot();
			scene.update(input, camera);
		}
		/* GAMEPLAY */
		if (scene.playerIsDead()) gameState = GAMEOVER_MENU;	// Game end (lose)
		else if (scene.isLevelCompleted()) {
			bool end = scene.isLastLevel();
			if (!end) gameState = CONGRATS_MENU;	// Game end (win)
			else gameState = NEXT_LEVEL_MENU;		// Next level
		}
	}
	/* MENUS */ 
	else {
		switch (gameState) {
		case MAIN_MENU:			menus.setActiveMenu(MAIN); break;
		case INSTRUCTIONS_MENU: menus.setActiveMenu(INSTRUCTIONS); break;
		case PAUSE_MENU:		menus.setActiveMenu(PAUSE); break;
		case GAMEOVER_MENU:		menus.setActiveMenu(GAME_OVER); break;
		case CONGRATS_MENU:		menus.setActiveMenu(CONGRATULATIONS); break;
		case NEXT_LEVEL_MENU:	menus.setActiveMenu(NEXT_LEVEL); break;
		default: break;
		}

		menus.resolveActiveMenuInput(input);
		MenuOption m = menus.getActiveMenuSelected();
		// Change the game state depending on the selected option
		switch (m) {
		case START_GAME:
			// TODO: data.stopAllSounds();
			//data.stopSound(GameData::INTRO_THEME_INDEX);
			gameState = PLAYING;
			scene.loadLevel(1);		// Start first level
			break;
		case SHOW_INSTRUCTIONS: gameState = INSTRUCTIONS_MENU; break;
		case QUIT_GAME: gameState = EXIT; break;
		case TO_MAIN_MENU: 
			// TODO: data.stopAllSounds();
			//data.stopSound(GameData::JUNGLE_THEME_INDEX);
			//data.stopSound(GameData::BOSS_THEME_INDEX);
			//data.stopSound(GameData::GAME_OVER_INDEX);
			//if (data.isSoundPlaying(GameData::ENDING_THEME_INDEX) )data.stopSound(GameData::ENDING_THEME_INDEX);
			gameState = MAIN_MENU; 
			break;
		case RESTART_GAME: gameState = PLAYING; break;
		case TO_NEXT_LEVEL:
			scene.nextLevel();
			// TODO: data.stopAllSounds();
			//data.stopSound(GameData::STAGE_CLEAR_INDEX);
			gameState = PLAYING;
			break;
		default: break;
		}
		menus.updateActiveMenu();
	}

	return gameState != EXIT;
}

/* Render */
void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (gameState == PLAYING) {
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(45.0, (float)SCREEN_WIDTH/(float)SCREEN_HEIGHT, 0.1, 10000);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		
		/* Drawing */
		camera.useActiveCamera();
		scene.drawEntity(true);
		scene.render(data);
	}
	else menus.renderActiveMenu(data);
	
	glutSwapBuffers();
}
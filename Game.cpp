
#include "Game.h"
#include <gl/glut.h>
#include <cmath>
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
	if (!data.loadSounds()) return false;

	// Scene initialization
	scene.init(SCREEN_WIDTH, SCREEN_HEIGHT);

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
			scene.resolveInput(input);
			scene.update(camera);
		}
		/* GAMEPLAY */
		if (scene.playerIsDead()) {
			gameState = GAMEOVER_MENU;			// Game end (lose)
			data.stopAllSounds();
			data.playSound(GameData::GAME_OVER_INDEX);
		} 
		else if (scene.isLevelCompleted()) {
			if (scene.isLastLevel()) {
				gameState = CONGRATS_MENU;		// Game end (win)
				data.stopAllSounds();
				data.playSound(GameData::ENDING_THEME_INDEX);
			}
			else {
				gameState = NEXT_LEVEL_MENU;	// Next level
				data.stopAllSounds();
				data.playSound(GameData::STAGE_CLEAR_INDEX);
			}
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
		bool notInstructions = gameState != INSTRUCTIONS_MENU;
		int level = scene.getCurrentLevel();
		switch (m) {
		case START_GAME:
			gameState = PLAYING;
			data.stopAllSounds();
			data.playSound(GameData::JUNGLE_THEME_INDEX);
			scene.loadLevel(1);		// Start first level
			break;
		case RESTART_GAME: 
			gameState = PLAYING; 
			//data.stopAllSounds();
			break;
		case TO_MAIN_MENU:
			gameState = MAIN_MENU;
			if (notInstructions) {
				data.stopAllSounds();
				data.playSound(GameData::INTRO_THEME_INDEX);
			}
			break;
		case TO_NEXT_LEVEL:
			gameState = PLAYING;
			data.stopAllSounds();
			scene.nextLevel();
			if (level == 1) {
				// current level = 2
				data.playSound(GameData::SNOW_FIELD_THEME);
			} else {
				// current level = 3
				data.playSound(GameData::BOSS_THEME_INDEX);
			}
			break;
		case SHOW_INSTRUCTIONS: gameState = INSTRUCTIONS_MENU; break;
		case QUIT_GAME: gameState = EXIT; break;
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
		scene.render(data);
	}
	else menus.renderActiveMenu(data);
	
	glutSwapBuffers();
}
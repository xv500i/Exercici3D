
#include "Game.h"
#include "Globals.h"
#include <cmath>
#include <time.h>
#include <random>


Game::Game(void) {}
Game::~Game(void) {}


bool Game::init()
{
	bool res = true;

	// Random seed
	srand((unsigned)time(0));
	
	//Graphics initialization
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (float)SCREEN_WIDTH/(float)SCREEN_HEIGHT, 0.1, 100);
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
	Scene.Init();
	gameState = MAIN_MENU;

	// Menu creation
	mainMenu.createMain();
	instructionsMenu.createInstructions();
	pauseMenu.createPause();
	gameOverMenu.createGameOver();
	congratsMenu.createCongrats();
	nextLevelMenu.createLevelCompleted();
	
	debug = true;
	data.playSound(GameData::INTRO_THEME_INDEX);

	return res;
}

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

void Game::finalize()
{
}


//Input
void Game::readKeyboard(unsigned char key, int x, int y, bool press)
{
	input.setKeyState(key, press);
}

void Game::readMouse(int button, int state, int x, int y) 
{
	if (button == -1) input.setMousePosition(x, y);
	else input.setMouseButtonState(button, state);
}


//Process
bool Game::process()
{
	bool res = true;

	MenuOption m;
	switch(gameState) {
	/* PLAYING */
	case PLAYING:
		
		if (input.keyIsDown('p')) gameState = PAUSE_MENU;
		else {
			// Active camera
			if (input.keyIsDown('1')) camera.setActiveCamera(FREE);
			if (input.keyIsDown('2')) camera.setActiveCamera(STATIC1);
			if (input.keyIsDown('3')) camera.setActiveCamera(STATIC2);
			if (input.keyIsDown('4')) camera.setActiveCamera(STATIC3);
			if (input.keyIsDown('5')) camera.setActiveCamera(STATIC4);

			// Polygon Mode
			if (input.keyIsDown('z')) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);  
			else if (input.keyIsDown('x')) glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			
			// Scene update
			Scene.update(input);
		}
		if (Scene.playerIsDead()) gameState = GAMEOVER_MENU;
		else if (Scene.isLevelCompleted()) {
			bool end = Scene.isLastLevel();
			if (!end) gameState = GAMEOVER_MENU;	// Game end
			else gameState = NEXT_LEVEL_MENU;		// Next level
		}
		break;

	/* MENUS */ 
	case MAIN_MENU:
		if (input.keyIsDown('s')) mainMenu.downPressed();
		else if (input.keyIsDown('w')) mainMenu.upPressed();
		else if (input.keyIsDown(' ')) mainMenu.enterPressed();

		m = mainMenu.getSelected();
		if (m == START) {
			data.stopSound(GameData::INTRO_THEME_INDEX);
			gameState = PLAYING;
			// init and start first lvl
			Scene.loadLevel(1);
		}
		else if (m == INSTRUCTIONS) gameState = INSTRUCTIONS_MENU;
		else if (m == QUIT) gameState = EXIT;
		mainMenu.update();
		break;

	case INSTRUCTIONS_MENU:
		if (input.keyIsDown('s')) instructionsMenu.downPressed();
		else if (input.keyIsDown('w')) instructionsMenu.upPressed();
		else if (input.keyIsDown(' ')) instructionsMenu.enterPressed();

		m = instructionsMenu.getSelected();
		if (m == TO_MAIN_MENU) gameState = MAIN_MENU;
		instructionsMenu.update();
		break;

	case PAUSE_MENU:
		if (input.keyIsDown('s')) pauseMenu.downPressed();
		else if (input.keyIsDown('w')) pauseMenu.upPressed();
		else if (input.keyIsDown(' ')) pauseMenu.enterPressed();

		m = pauseMenu.getSelected();
		if (m == RESTART) gameState = PLAYING;
		else if (m == TO_MAIN_MENU) {
			gameState = MAIN_MENU;
			data.stopSound(GameData::JUNGLE_THEME_INDEX);
			data.stopSound(GameData::BOSS_THEME_INDEX);
		}
		else if (m == QUIT) gameState = EXIT;
		pauseMenu.update();
		break;

	case GAMEOVER_MENU:
		if (input.keyIsDown('s')) gameOverMenu.downPressed();
		else if (input.keyIsDown('w')) gameOverMenu.upPressed();
		else if (input.keyIsDown(' ')) gameOverMenu.enterPressed();
	
		m = gameOverMenu.getSelected();
		if (m == TO_MAIN_MENU) {
			data.stopSound(GameData::GAME_OVER_INDEX);
			gameState = MAIN_MENU;
		} else if (m == QUIT) gameState = EXIT;
		gameOverMenu.update();
		break;

	case CONGRATS_MENU:
		if (input.keyIsDown('s')) congratsMenu.downPressed();
		else if (input.keyIsDown('w')) congratsMenu.upPressed();
		else if (input.keyIsDown(' ')) congratsMenu.enterPressed();
		m = congratsMenu.getSelected();
		if (m == TO_MAIN_MENU) {
			gameState = MAIN_MENU;
			if (data.isSoundPlaying(GameData::ENDING_THEME_INDEX) )data.stopSound(GameData::ENDING_THEME_INDEX);
		}
		else if (m == QUIT) {
			gameState = EXIT;
		}
		congratsMenu.update();
		break;

	case NEXT_LEVEL_MENU:
		if (input.keyIsDown('s')) nextLevelMenu.downPressed();
		else if (input.keyIsDown('w')) nextLevelMenu.upPressed();
		else if (input.keyIsDown(' ')) nextLevelMenu.enterPressed();
		m = nextLevelMenu.getSelected();
		if (m == NEXT_LEVEL) {
			// init and start next lvl
			Scene.nextLevel();
			data.stopSound(GameData::STAGE_CLEAR_INDEX);
			gameState = PLAYING;
		}
		else if (m == TO_MAIN_MENU) {
			gameState = MAIN_MENU;
		}
		nextLevelMenu.update();
		break;
	}

	return gameState != EXIT && res;
}

//Output
void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	//encapsulateDrawing();
	
	switch (gameState) {
	case PLAYING:
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(45.0, (float)SCREEN_WIDTH/(float)SCREEN_HEIGHT, 0.1, 100);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		
		/* Drawing */
		camera.useActiveCamera();
		Scene.drawEntity(true);
		Scene.render(data);
		
		break;
	case MAIN_MENU:			
		mainMenu.render(&data); break;
	case PAUSE_MENU:		pauseMenu.render(&data); break;
	case GAMEOVER_MENU:		gameOverMenu.render(&data); break;
	case INSTRUCTIONS_MENU:	instructionsMenu.render(&data); break;
	case NEXT_LEVEL_MENU:	nextLevelMenu.render(&data); break;
	case CONGRATS_MENU:		congratsMenu.render(&data); break;
	}
	
	glutSwapBuffers();
}

/*void Game::encapsulateDrawing()
{	
	float eyeX, eyeY, eyeZ;
	camera.setUpVector(0.0f, 1.0f, 0.0f);
	camera.setReferencePoint(0.0f, 0.0f, 0.0f);

	eyeY = 15.0f;
	float module = 30.0f;
	switch (selectedCamera) {*/
	/*case 1:
		//Scene.getFirstPersonParameters(eyex,eyey,eyez,centerx,centery,centerz);
		 FIXME
		eyex = Scene.entityX;
		eyey = Scene.entityY/2;
		eyez = Scene.entityZ;
		centerx = eyex + 5*cos(Scene.angle * 3.1415f / 180.0f);
		centery = eyey;
		centerz = eyez + 5*sin(Scene.angle * 3.1415f / 180.0f);
		
		break;
	case 2:
		eyeX = module;
		eyeZ = 0;
		break;
	case 3:
		eyeX = 0;
		eyeZ = module;
		break;
	case 4:
		eyeX = -module;
		eyeZ = 0;
		break;
	case 5:
		eyeX = 0;
		eyeZ = -module;
		break;
	}
	camera.setEyePosition(eyeX, eyeY, eyeZ);*/

	// TODO: MOURE D'AQUI
	// Free Camera			
	/*float panX = 0.0f;
	float panY = 0.0f;
	float panZ = 0.0f;
	if (input.keyIsDown('o')) panZ += 1.0f;
	if (input.keyIsDown('l')) panZ -= 1.0f;
	if (input.keyIsDown('k')) panX -= 1.0f;
	if (input.keyIsDown('ñ')) panX += 1.0f;
	camera.pan(panX, panY, panZ);*/

	/*camera.use();

	Scene.drawEntity(selectedCamera != 1);
	Scene.render(data);
	//Scene.Draw(&Data);
}*/
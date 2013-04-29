#include "cGame.h"
#include "Globals.h"
#include <cmath>


cGame::cGame(void) {}
cGame::~cGame(void){}

bool cGame::init()
{
	bool res=true;
	
	//Graphics initialization
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (float)SCREEN_WIDTH/(float)SCREEN_HEIGHT, 0.1, 100);
	glMatrixMode(GL_MODELVIEW);
	
	glEnable(GL_DEPTH_TEST);
	glAlphaFunc(GL_GREATER, 0.05f);
	glEnable(GL_ALPHA_TEST);

	//Scene initialization
	/*
	res = Data.LoadImage(IMG_WALL,"wall.png",GL_RGBA);
	if(!res) return false;
	res = Data.LoadImage(IMG_FLOOR,"floor.png",GL_RGBA);
	if(!res) return false;
	res = Data.LoadImage(IMG_ROOF,"roof.png",GL_RGBA);
	if(!res) return false;
	*/
	if (!dataBona.loadTextures()) return false;
	if (!dataBona.loadTileSheets()) return false;
	if (!dataBona.loadSprites()) return false;
	if (!dataBona.loadSounds()) return false;

	Scene.Init();
	gameState = MAIN_MENU;
	mainMenu.createMain();
	instructionsMenu.createInstructions();
	pauseMenu.createPause();
	gameOverMenu.createGameOver();
	congratsMenu.createCongrats();
	nextLevelMenu.createLevelCompleted();
	debug = true;
	selectedCamera = 2;
	dataBona.playSound(GameData::INTRO_THEME_INDEX);
	return res;
}

bool cGame::loop()
{
	int t1, t2;

	t1 = glutGet(GLUT_ELAPSED_TIME);

	bool b = process();
	if (b) render();

	do {
		t2 = glutGet(GLUT_ELAPSED_TIME);
	} while (t2 - t1 < 20);

	if (!b) exit(0);
	return b;
}

void cGame::finalize()
{
}


//Input
void cGame::readKeyboard(unsigned char key, int x, int y, bool press)
{
	input.setKeyState(key, press);
}

void cGame::readMouse(int button, int state, int x, int y) 
{
	if (button == -1) input.setMousePosition(x, y);
	else input.setMouseButtonState(button, state);
}


//Process
bool cGame::process()
{
	bool res=true;
	
	//Process Input
	
	
	//Game Logic
	//...

	MenuOption m;
	switch(gameState) {
	case PLAYING:
		if (input.keyIsDown('p')) gameState = PAUSE_MENU;
		else {
			/*
			scene.resolveInput(input);
			scene.update(&data, &viewport);
			if (scene.playerHasLost()) {
				gameState = GAMEOVER_MENU;
				data.stopSound(GameData::JUNGLE_THEME_INDEX);
				data.stopSound(GameData::BOSS_THEME_INDEX);
				data.playSound(GameData::GAME_OVER_INDEX);
			}
			else if (scene.playerHasWon()) {
				data.stopSound(GameData::JUNGLE_THEME_INDEX);
				data.stopSound(GameData::BOSS_THEME_INDEX);
				if (scene.gameFinished()) {
					gameState = CONGRATS_MENU;
					data.playSound(GameData::ENDING_THEME_INDEX);
				} else {
					gameState = NEXT_LEVEL_MENU;
					
					data.playSound(GameData::STAGE_CLEAR_INDEX);
				}
			}*/
			if (input.keyIsDown(27))	res=false;
			if (input.keyIsDown('1'))	selectedCamera = 1;
			if (input.keyIsDown('2'))	selectedCamera = 2;
			if (input.keyIsDown('3'))	selectedCamera = 3;
			if (input.keyIsDown('4'))	selectedCamera = 4;
			if (input.keyIsDown('5'))	selectedCamera = 5;
			Scene.update(input);
		}
		break;

	case MAIN_MENU:
		if (input.keyIsDown('s')) mainMenu.downPressed();
		else if (input.keyIsDown('w')) mainMenu.upPressed();
		else if (input.keyIsDown(' ')) mainMenu.enterPressed();

		m = mainMenu.getSelected();
		if (m == START) {
			dataBona.stopSound(GameData::INTRO_THEME_INDEX);
			gameState = PLAYING;
			//viewport.init(0.0f, GAME_HEIGHT, GAME_WIDTH, GAME_HEIGHT);
			//scene.changeLevel(1, &data, &viewport);		// From the main menu, we start the first level
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
			dataBona.stopSound(GameData::JUNGLE_THEME_INDEX);
			dataBona.stopSound(GameData::BOSS_THEME_INDEX);
		}
		else if (m == QUIT) gameState = EXIT;
		pauseMenu.update();
		break;

	case GAMEOVER_MENU:
		if (input.keyIsDown('s')) gameOverMenu.downPressed();
		else if (input.keyIsDown('w')) gameOverMenu.upPressed();
		else if (input.keyIsDown(' ')) gameOverMenu.enterPressed();
	
		m = gameOverMenu.getSelected();
		if (m == TO_MAIN_MENU) gameState = MAIN_MENU;
		else if (m == QUIT) gameState = EXIT;
		gameOverMenu.update();
		break;
	case CONGRATS_MENU:
		if (input.keyIsDown('s')) congratsMenu.downPressed();
		else if (input.keyIsDown('w')) congratsMenu.upPressed();
		else if (input.keyIsDown(' ')) congratsMenu.enterPressed();
		m = congratsMenu.getSelected();
		if (m == TO_MAIN_MENU) {
			gameState = MAIN_MENU;
			if (dataBona.isSoundPlaying(GameData::ENDING_THEME_INDEX) )dataBona.stopSound(GameData::ENDING_THEME_INDEX);
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
			/*
			scene.changeToNextLevel(&data, &viewport);
			*/
			dataBona.stopSound(GameData::STAGE_CLEAR_INDEX);
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
void cGame::render()
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
		encapsulateDrawing(); break;
	case MAIN_MENU:			
		mainMenu.render(&dataBona); break;
	case PAUSE_MENU:		pauseMenu.render(&dataBona); break;
	case GAMEOVER_MENU:		gameOverMenu.render(&dataBona); break;
	case INSTRUCTIONS_MENU:	instructionsMenu.render(&dataBona); break;
	case NEXT_LEVEL_MENU:	nextLevelMenu.render(&dataBona); break;
	case CONGRATS_MENU:		congratsMenu.render(&dataBona); break;
	}
	
	glutSwapBuffers();
}

void cGame::encapsulateDrawing()
{	
	float eyeX, eyeY, eyeZ;
	camera.setUpVector(0.0f, 1.0f, 0.0f);
	camera.setReferencePoint(0.0f, 0.0f, 0.0f);

	eyeY = 20.0f;
	float module = 30.0f;
	switch (selectedCamera) {
	case 1:
		//Scene.getFirstPersonParameters(eyex,eyey,eyez,centerx,centery,centerz);
		/* FIXME
		eyex = Scene.entityX;
		eyey = Scene.entityY/2;
		eyez = Scene.entityZ;
		centerx = eyex + 5*cos(Scene.angle * 3.1415f / 180.0f);
		centery = eyey;
		centerz = eyez + 5*sin(Scene.angle * 3.1415f / 180.0f);
		*/
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
	camera.setEyePosition(eyeX, eyeY, eyeZ);
	camera.use();

	Scene.drawEntity(selectedCamera != 1);
	Scene.render(dataBona);
	//Scene.Draw(&Data);
}
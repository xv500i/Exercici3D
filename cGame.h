#pragma once

#include "cScene.h"
#include "cData.h"
#include "InputHandler.h"
#include "Camera.h"

#define SCREEN_WIDTH	800
#define SCREEN_HEIGHT	600

class cGame
{
private:
	InputHandler input;
	Camera camera;
	cScene Scene;
	cData Data;
	bool debug;
	int selectedCamera;
	

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
};

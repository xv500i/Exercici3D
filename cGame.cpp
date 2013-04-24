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
	res = Data.LoadImage(IMG_WALL,"wall.png",GL_RGBA);
	if(!res) return false;
	res = Data.LoadImage(IMG_FLOOR,"floor.png",GL_RGBA);
	if(!res) return false;
	res = Data.LoadImage(IMG_ROOF,"roof.png",GL_RGBA);
	if(!res) return false;
	selectedCamera = 2;
	Scene.Init();
	debug = true;
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
	if (input.keyIsDown(27))	res=false;
	if (input.keyIsDown('1'))	selectedCamera = 1;
	if (input.keyIsDown('2'))	selectedCamera = 2;
	if (input.keyIsDown('3'))	selectedCamera = 3;
	if (input.keyIsDown('4'))	selectedCamera = 4;
	if (input.keyIsDown('5'))	selectedCamera = 5;
	Scene.update(input);
	//Game Logic
	//...

	return res;
}

//Output
void cGame::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
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
	Scene.Draw(&Data);
	
	glutSwapBuffers();
}

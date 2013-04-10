#include "cGame.h"
#include "Globals.h"
#include <cmath>

cGame::cGame(void) {}
cGame::~cGame(void){}

bool cGame::Init()
{
	bool res=true;

	//Graphics initialization
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0,(float)SCREEN_WIDTH/(float)SCREEN_HEIGHT,0.1,100);
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
	debug = false;
	return res;
}

bool cGame::Loop()
{
	int t1, t2;

	t1 = glutGet(GLUT_ELAPSED_TIME);

	bool b = Process();
	if (b) Render();

	do {
		t2 = glutGet(GLUT_ELAPSED_TIME);
	} while (t2 - t1 < 20);

	if (!b) exit(0);
	return b;
}

void cGame::Finalize()
{
}

//Input
void cGame::ReadKeyboard(unsigned char key, int x, int y, bool press)
{
	keys[key] = press;
}

void cGame::ReadMouse(int button, int state, int x, int y)
{
}

//Process
bool cGame::Process()
{
	bool res=true;
	
	//Process Input
	if(keys[27])	res=false;
	if(keys['1']) selectedCamera = 1;
	else if(keys['2']) selectedCamera = 2;
	else if(keys['3']) selectedCamera = 3;
	else if(keys['4']) selectedCamera = 4;
	else if(keys['5']) selectedCamera = 5;
	Scene.resolveInput(keys);
	//Game Logic
	//...

	return res;
}

//Output
void cGame::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	
	float eyex, eyey, eyez, centerx, centery, centerz, upx, upy, upz;
	upx = upz = 0.0f;
	upy = 1.0f;
	eyey = 20.0f;
	centerx = centery = centerz = 0.0f;
	float module = 30.0f;
	switch (selectedCamera) {
	case 1:
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
		eyex = +module;
		eyez = 0;
		break;
	case 3:
		eyex = 0;
		eyez = +module;
		break;
	case 4:
		eyex = -module;
		eyez = 0;
		
		break;
	case 5:
		eyex = 0;
		eyez = -module;
		break;
	}

	gluLookAt(eyex, eyey, eyez, centerx, centery, centerz, upx, upy, upz);

	if (debug) {
		glLineWidth(3.0f);
		glBegin(GL_LINES);

		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(10000.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);

		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0.0f, 10000.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);

		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(0.0f, 0.0f, 10000.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);

		glColor3f(1.0f, 1.0f, 1.0f);

		glEnd();
		
	}

	Scene.drawEntity(selectedCamera != 1);
	Scene.Draw(&Data);

	glutSwapBuffers();
}

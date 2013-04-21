
#include "Globals.h"
#include "cGame.h"

//Delete console
//#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

cGame game;


void appRender()
{
	game.render();
}

void appKeyboard(unsigned char key, int x, int y)
{
	game.readKeyboard(key, x, y, true);
}

void appKeyboardUp(unsigned char key, int x, int y)
{
	game.readKeyboard(key, x, y, false);
}

void appSpecialKeys(int key, int x, int y)
{
	game.readKeyboard(key, x, y, true);
}

void appSpecialKeysUp(int key, int x, int y)
{
	game.readKeyboard(key, x, y, false);
}

void appMouseButtons(int button, int state, int x, int y)
{
	game.readMouse(button, state, x, y);
}

void appMousePosition(int x, int y)
{
	game.readMouse(-1, -1, x, y);
}

void appIdle()
{
	if (!game.loop()) exit(0);
}

void main(int argc, char** argv)
{
	int res_x, res_y, pos_x, pos_y;

	// GLUT initialization
	glutInit(&argc, argv);

	// RGBA with double buffer
	glutInitDisplayMode(GLUT_RGBA | GLUT_ALPHA | GLUT_DOUBLE);

	// Create centered window
	res_x = glutGet(GLUT_SCREEN_WIDTH);
	res_y = glutGet(GLUT_SCREEN_HEIGHT);
	pos_x = (res_x>>1) - (SCREEN_WIDTH>>1);
	pos_y = (res_y>>1) - (SCREEN_HEIGHT>>1);
	
	glutInitWindowPosition(pos_x, pos_y);
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutCreateWindow("My Awesome 3D Game!");

	// Full Screen
	/*glutGameModeString("800x600:32");
	glutEnterGameMode();*/

	//Make the default cursor disappear
	//glutSetCursor(GLUT_CURSOR_NONE);

	//Register callback functions
	glutDisplayFunc(appRender);			
	glutKeyboardFunc(appKeyboard);		
	glutKeyboardUpFunc(appKeyboardUp);	
	glutSpecialFunc(appSpecialKeys);	
	glutSpecialUpFunc(appSpecialKeysUp);
	glutMouseFunc(appMouseButtons);
	glutMotionFunc(appMousePosition);
	glutPassiveMotionFunc(appMousePosition);
	glutIdleFunc(appIdle);

	//Game initializations
	game.init();

	//Application loop
	glutMainLoop();	
}
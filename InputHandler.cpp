
#include "InputHandler.h"
#include <gl/glut.h>


InputHandler::InputHandler(void)
{
	resetDefaults();
}

InputHandler::~InputHandler(void) {}


/* Reset key defaults */
void InputHandler::resetDefaults()
{
	/* Player movement */
	keyMap[MOVE_FORWARD] = DEFAULT_MOVE_FORWARD_KEY;
	keyMap[MOVE_BACKWARD] = DEFAULT_MOVE_BACKWARD_KEY;
	keyMap[ROTATE_LEFT] = DEFAULT_ROTATE_LEFT_KEY;
	keyMap[ROTATE_RIGHT] = DEFAULT_ROTATE_RIGHT_KEY;
	keyMap[MOVE_LEFT] = DEFAULT_MOVE_LEFT_KEY;
	keyMap[MOVE_RIGHT] = DEFAULT_MOVE_RIGHT_KEY; 
	keyMap[JUMP] = DEFAULT_JUMP_KEY;
	/* Menu */
	keyMap[MENU_UP] = DEFAULT_MENU_UP_KEY;
	keyMap[MENU_DOWN] = DEFAULT_MENU_DOWN_KEY;
	keyMap[MENU_SELECTION] = DEFAULT_MENU_SELECTION_KEY;
	keyMap[SHOW_PAUSE_MENU] = DEFAULT_PAUSE_MENU_KEY;
	/* Camera selection */
	keyMap[THIRD_PERSON_CAMERA] = DEFAULT_THIRD_PERSON_CAMERA_KEY;
	keyMap[FREE_CAMERA] = DEFAULT_FREE_CAMERA_KEY;
	keyMap[STATIC1_CAMERA] = DEFAULT_STATIC1_CAMERA_KEY;
	keyMap[STATIC2_CAMERA] = DEFAULT_STATIC2_CAMERA_KEY;
	keyMap[STATIC3_CAMERA] = DEFAULT_STATIC3_CAMERA_KEY;
	keyMap[STATIC4_CAMERA] = DEFAULT_STATIC4_CAMERA_KEY;
	/* Free camera movement */
	keyMap[CAMERA_MOVE_FORWARD] = DEFAULT_CAMERA_MOVE_FORWARD_KEY;
	keyMap[CAMERA_MOVE_BACKWARD] = DEFAULT_CAMERA_MOVE_BACKWARD_KEY;
	keyMap[CAMERA_MOVE_LEFT] = DEFAULT_CAMERA_MOVE_LEFT_KEY;
	keyMap[CAMERA_MOVE_RIGHT] = DEFAULT_CAMERA_MOVE_RIGHT_KEY;
	keyMap[CAMERA_ROTATE_LEFT] = DEFAULT_CAMERA_ROTATE_LEFT_KEY;
	keyMap[CAMERA_ROTATE_RIGHT] = DEFAULT_CAMERA_ROTATE_RIGHT_KEY;
	/* Polygon mode */
	keyMap[WIREFRAME_MODE] = DEFAULT_WIREFRAME_MODE_KEY;
	keyMap[FILL_MODE] = DEFAULT_FILL_MODE_KEY;
}


/* Set keyboard and mouse state (GLUT callbacks) */
void InputHandler::setKeyState(unsigned char key, bool down) 
{
	keys[key] = down;
}

void InputHandler::setMouseButtonState(int button, int state)
{
	switch (button) {
	case GLUT_LEFT_BUTTON:	
		if (state == GLUT_DOWN) leftMouseButton = true;
		else leftMouseButton = false;
		break;
	case GLUT_RIGHT_BUTTON:
		if (state == GLUT_DOWN) rightMouseButton = true;
		else rightMouseButton = false;
		break;
	default: break;
	}
}

void InputHandler::setMousePosition(int x, int y)
{
	mouseX = x;
	mouseY = y;
}


/* Get keyboard and mouse state */
bool InputHandler::keyIsDown(unsigned char key)
{
	// IMPORTANT NOTE: We supose that keys with ASCII code 0 and 2 are not used (NULL and STX [text start])
	switch (key) {
	case GLUT_LEFT_BUTTON:	return leftMouseButton;
	case GLUT_RIGHT_BUTTON: return rightMouseButton;
	default:				return keys[key];
	}
}

void InputHandler::getMousePosition(int &x, int &y)
{
	x = mouseX;
	y = mouseY;
}


/* Key configuration */
unsigned char InputHandler::getKey(Key key)
{
	return keyMap[key];
}

void InputHandler::setKey(Key key, unsigned char newKeyValue)
{
	keyMap[key] = newKeyValue;
}
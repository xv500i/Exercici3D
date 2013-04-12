
#include "InputHandler.h"


InputHandler::InputHandler(void)
{
	resetDefaults();
}

InputHandler::~InputHandler(void) {}


/* Reset key defaults */
void InputHandler::resetDefaults()
{
	// Movement keys
	moveForwardKey = DEFAULT_MOVEFORWARD_KEY;
	moveBackwardKey = DEFAULT_MOVEBACKWARD_KEY;
	rotateLeftKey = DEFAULT_ROTATELEFT_KEY;
	rotateRightKey = DEFAULT_ROTATERIGHT_KEY;
	moveLeftKey = DEFAULT_MOVELEFT_KEY;
	moveRightKey = DEFAULT_MOVERIGHT_KEY; 
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
	switch (key) {
	case MOVE_FORWARD:		return moveForwardKey;
	case MOVE_BACKWARD:		return moveBackwardKey;
	case ROTATE_LEFT:		return rotateLeftKey;
	case ROTATE_RIGHT:		return rotateRightKey;
	case MOVE_LEFT:			return moveLeftKey;
	case MOVE_RIGHT:		return moveRightKey;
	default: return -1;
	}
}

void InputHandler::setKey(Key key, unsigned char newKeyValue)
{
	switch (key) {
	case MOVE_FORWARD:		moveForwardKey = newKeyValue;
	case MOVE_BACKWARD:		moveBackwardKey = newKeyValue;
	case ROTATE_LEFT:		rotateLeftKey = newKeyValue;
	case ROTATE_RIGHT:		rotateRightKey = newKeyValue;
	case MOVE_LEFT:			moveLeftKey = newKeyValue;
	case MOVE_RIGHT:		moveRightKey = newKeyValue;
	default: break;
	}
}
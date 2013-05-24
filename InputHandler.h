
#pragma once

#include <map>


enum Key {
	/* Player movement */
	MOVE_FORWARD,
	MOVE_BACKWARD,
	MOVE_LEFT,
	MOVE_RIGHT,
	ROTATE_LEFT,
	ROTATE_RIGHT,
	JUMP,
	/* Menu */
	MENU_UP,
	MENU_DOWN,
	MENU_SELECTION,
	SHOW_PAUSE_MENU,
	/* Camera selection */
	THIRD_PERSON_CAMERA,
	FREE_CAMERA,
	STATIC1_CAMERA,
	STATIC2_CAMERA,
	STATIC3_CAMERA,
	STATIC4_CAMERA,
	/* Free camera movement */
	CAMERA_MOVE_FORWARD,
	CAMERA_MOVE_BACKWARD,
	CAMERA_MOVE_LEFT,
	CAMERA_MOVE_RIGHT,
	CAMERA_ROTATE_LEFT,
	CAMERA_ROTATE_RIGHT,
	/* Polygon mode */
	WIREFRAME_MODE,
	FILL_MODE
};


class InputHandler
{
private:
	/* Min and max keys */
	const static unsigned char MIN_KEY = 0;
	const static unsigned char MAX_KEY = 255;

	/* Default keys */
	const static unsigned char DEFAULT_MOVE_FORWARD_KEY = 'w';
	const static unsigned char DEFAULT_MOVE_BACKWARD_KEY = 's';
	const static unsigned char DEFAULT_MOVE_LEFT_KEY = 'a';
	const static unsigned char DEFAULT_MOVE_RIGHT_KEY = 'd';
	const static unsigned char DEFAULT_ROTATE_LEFT_KEY = 'q';
	const static unsigned char DEFAULT_ROTATE_RIGHT_KEY = 'e';
	const static unsigned char DEFAULT_JUMP_KEY = ' ';
	const static unsigned char DEFAULT_MENU_UP_KEY = 'w';
	const static unsigned char DEFAULT_MENU_DOWN_KEY = 's';
	const static unsigned char DEFAULT_MENU_SELECTION_KEY = ' ';
	const static unsigned char DEFAULT_PAUSE_MENU_KEY = 'p';
	const static unsigned char DEFAULT_THIRD_PERSON_CAMERA_KEY = '1';
	const static unsigned char DEFAULT_FREE_CAMERA_KEY = '2';
	const static unsigned char DEFAULT_STATIC1_CAMERA_KEY = '3';
	const static unsigned char DEFAULT_STATIC2_CAMERA_KEY = '4';
	const static unsigned char DEFAULT_STATIC3_CAMERA_KEY = '5';
	const static unsigned char DEFAULT_STATIC4_CAMERA_KEY = '6';
	const static unsigned char DEFAULT_CAMERA_MOVE_FORWARD_KEY = 'i';
	const static unsigned char DEFAULT_CAMERA_MOVE_BACKWARD_KEY = 'k';
	const static unsigned char DEFAULT_CAMERA_MOVE_LEFT_KEY = 'j';
	const static unsigned char DEFAULT_CAMERA_MOVE_RIGHT_KEY = 'l';
	const static unsigned char DEFAULT_CAMERA_ROTATE_LEFT_KEY = 'u';
	const static unsigned char DEFAULT_CAMERA_ROTATE_RIGHT_KEY = 'o';
	const static unsigned char DEFAULT_WIREFRAME_MODE_KEY = 'z';
	const static unsigned char DEFAULT_FILL_MODE_KEY = 'x';

	std::map<Key, unsigned char> keyMap;	/* Key mapping */

	/* KEYBOARD */
	bool keys[256];		/* Keyboard keys array */

	/* MOUSE */
	bool leftMouseButton;
	bool rightMouseButton;
	int mouseX;
	int mouseY;

public:
	InputHandler(void);
	~InputHandler(void);

	/* Reset key defaults */
	void resetDefaults();

	/* Set keyboard and mouse state (GLUT callbacks) */
	void setKeyState(unsigned char key, bool down);
	void setMouseButtonState(int button, int state);
	void setMousePosition(int x, int y);

	/* Get keyboard and mouse state */
	bool keyIsDown(unsigned char key);
	void getMousePosition(int &x, int &y);

	/* Key configuration */
	unsigned char getKey(Key key);
	void setKey(Key key, unsigned char newKeyValue);
};
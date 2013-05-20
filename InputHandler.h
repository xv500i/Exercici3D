
#pragma once


enum Key {
	MOVE_FORWARD,
	MOVE_BACKWARD,
	MOVE_LEFT,
	MOVE_RIGHT,
	ROTATE_LEFT,
	ROTATE_RIGHT,
};


class InputHandler
{
private:
	/* Min and max keys */
	const static unsigned char MIN_KEY = 0;
	const static unsigned char MAX_KEY = 255;

	/* Default keys */
	const static unsigned char DEFAULT_MOVEFORWARD_KEY = 'w';
	const static unsigned char DEFAULT_MOVEBACKWARD_KEY = 's';
	const static unsigned char DEFAULT_MOVELEFT_KEY = 'a';
	const static unsigned char DEFAULT_MOVERIGHT_KEY = 'd';
	const static unsigned char DEFAULT_ROTATELEFT_KEY = 'q';
	const static unsigned char DEFAULT_ROTATERIGHT_KEY = 'e';

	/* Movement keys */
	unsigned char moveForwardKey;
	unsigned char moveBackwardKey;
	unsigned char moveLeftKey;
	unsigned char moveRightKey;
	unsigned char rotateLeftKey;
	unsigned char rotateRightKey;

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
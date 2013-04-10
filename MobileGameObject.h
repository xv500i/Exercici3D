#pragma once
#include "gameobject.h"
class MobileGameObject :
	public GameObject
{
public:
	MobileGameObject(void);
	~MobileGameObject(void);
	void update();
	void moveForward();
	void moveBackwards();
	void moveLeft();
	void moveRight();
	void turnLeft();
	void turnRight();
private:
	float velocity;
	float turnAnglePerStep;
};


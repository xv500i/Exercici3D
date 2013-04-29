#pragma once
#include "gameobject.h"
#include "Vector3D.h"
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
	float maxAcceleration;
	float friction;
	float maxVelocity;
	Vector3D velocity;
	Vector3D acceleration;
	float turnAnglePerStep;
};


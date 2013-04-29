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
	bool jump();
	void floorReached();
	void render() const;
	void clearYVelocity();
private:
	float gravity;
	bool footOnGround;
	float jumpAcceleration;
	float jumpImpulse;
	float maxAcceleration;
	float friction;
	float maxVelocity;
	Vector3D velocity;
	Vector3D acceleration;
	float turnAnglePerStep;
};


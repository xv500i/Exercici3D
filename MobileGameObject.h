#pragma once
#include "gameobject.h"
#include "Vector3D.h"
#include <vector>

class MobileGameObject : public GameObject
{
public:
	MobileGameObject(void);
	~MobileGameObject(void);
	void update(Vector3D &inclination, std::vector<GameObject*> &objects);
	void moveForward();
	void moveBackwards();
	void moveLeft();
	void moveRight();
	void moveForwardLeft();
	void moveForwardRight();
	void moveBackwardLeft();
	void moveBackwardRight();
	void turnLeft();
	void turnRight();
	bool jump();
	void floorReached();
	void render(GameData &data) const;
	void clearYVelocity();
	void setXVelocity(float v);
	void setZVelocity(float v);
	void setYVelocity(float v);
	float getXVelocity();
	float getZVelocity();
	float getYVelocity();
	void sliding(GameObject *go);
	Vector3D getInclination() const;
	void setFriction(float f);
	void setGravity(float f);
	void setMaxAcceleration(float f);
	
private:
	virtual void tractarColisions(std::vector<GameObject*> &objects);
	float gravity;
	bool footOnGround;
	float jumpAcceleration;
	float jumpImpulse;
	float maxAcceleration;
	float friction;
	float maxVelocity;
	Vector3D velocity;
	Vector3D acceleration;
	Vector3D inclination;
	float turnAnglePerStep;
};


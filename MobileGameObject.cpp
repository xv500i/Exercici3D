#include "MobileGameObject.h"


MobileGameObject::MobileGameObject(void) : GameObject()
{
	velocity = 0.5f;
	turnAnglePerStep = 0.4f;
}


MobileGameObject::~MobileGameObject(void)
{
}

void MobileGameObject::update()
{
	GameObject::update();
}

void MobileGameObject::turnLeft()
{
	setYAngle( getYAngle() + turnAnglePerStep );
}

void MobileGameObject::turnRight()
{
	setYAngle( getYAngle() - turnAnglePerStep );
}

void MobileGameObject::moveForward()
{
	setXPosition( getXPosition() + velocity);
}

void MobileGameObject::moveBackwards()
{

}

void MobileGameObject::moveLeft()
{

}

void MobileGameObject::moveRight()
{

}
#include "MobileGameObject.h"
#include <cmath>

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
	setYAngle( getYAngle() - turnAnglePerStep );
}

void MobileGameObject::turnRight()
{
	setYAngle( getYAngle() + turnAnglePerStep );
}

void MobileGameObject::moveForward()
{
	setXPosition( getXPosition() + velocity*cos(getYAngle() * 3.1415f / 180.0f));
	setZPosition( getZPosition() + velocity*sin(getYAngle() * 3.1415f / 180.0f));
}

void MobileGameObject::moveBackwards()
{
	setXPosition( getXPosition() - velocity*cos(getYAngle() * 3.1415f / 180.0f));
	setZPosition( getZPosition() - velocity*sin(getYAngle() * 3.1415f / 180.0f));
}

void MobileGameObject::moveLeft()
{
	setXPosition( getXPosition() + velocity*cos((getYAngle() + 90.f) * 3.1415f / 180.0f));
	setZPosition( getZPosition() + velocity*sin((getYAngle() + 90.f) * 3.1415f / 180.0f));
}

void MobileGameObject::moveRight()
{
	setXPosition( getXPosition() + velocity*cos((getYAngle() - 90.f) * 3.1415f / 180.0f));
	setZPosition( getZPosition() + velocity*sin((getYAngle() - 90.f) * 3.1415f / 180.0f));
}
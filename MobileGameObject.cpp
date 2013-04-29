#include "MobileGameObject.h"
#include <cmath>

MobileGameObject::MobileGameObject(void) : GameObject()
{
	maxVelocity = 0.9f;
	maxAcceleration = 0.1f;
	friction = 0.95f;
	turnAnglePerStep = 5.0f;
	velocity = Vector3D();
	acceleration = Vector3D();
}


MobileGameObject::~MobileGameObject(void)
{
}

void MobileGameObject::update()
{
	GameObject::update();
	// acceleration does not take in account gravity, which is calculated apart!
	if (acceleration.getModule() > maxAcceleration) {
		// restrict maximum acceleration
		acceleration.normalize();
		acceleration *= maxAcceleration;
	}
	//acceleration.setX(1.0f);
	velocity += acceleration;
	if (velocity.getModule() > maxVelocity) {
		// restrict maximum velocity
		velocity.normalize();
		velocity *= maxVelocity;
	}
	setXPosition( getXPosition() + velocity.getX() );
	setZPosition( getZPosition() + velocity.getZ() );
	// Friction
	velocity *= friction;
	// clear accelerations
	acceleration.setX(0.0f);
	acceleration.setY(0.0f);
	acceleration.setZ(0.0f);
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
	
	//setXPosition( getXPosition() + maxVelocity*cos(getYAngle() * 3.1415f / 180.0f));
	//setZPosition( getZPosition() + maxVelocity*sin(getYAngle() * 3.1415f / 180.0f));
	
	acceleration.setX( maxAcceleration*cos(getYAngle() * 3.1415f / 180.0f) );
	acceleration.setZ( maxAcceleration*sin(getYAngle() * 3.1415f / 180.0f) );
}

void MobileGameObject::moveBackwards()
{
	//setXPosition( getXPosition() - maxVelocity*cos(getYAngle() * 3.1415f / 180.0f));
	//setZPosition( getZPosition() - maxVelocity*sin(getYAngle() * 3.1415f / 180.0f));
	acceleration.setX( -maxAcceleration*cos(getYAngle() * 3.1415f / 180.0f) );
	acceleration.setZ( -maxAcceleration*sin(getYAngle() * 3.1415f / 180.0f) );
}

void MobileGameObject::moveLeft()
{
	//setXPosition( getXPosition() + maxVelocity*cos((getYAngle() - 90.f) * 3.1415f / 180.0f));
	//setZPosition( getZPosition() + maxVelocity*sin((getYAngle() - 90.f) * 3.1415f / 180.0f));
	acceleration.setX( maxAcceleration*cos((getYAngle() -90.0f) * 3.1415f / 180.0f) );
	acceleration.setZ( maxAcceleration*sin((getYAngle() -90.0f) * 3.1415f / 180.0f) );
}

void MobileGameObject::moveRight()
{
	//setXPosition( getXPosition() + maxVelocity*cos((getYAngle() + 90.f) * 3.1415f / 180.0f));
	//setZPosition( getZPosition() + maxVelocity*sin((getYAngle() + 90.f) * 3.1415f / 180.0f));
	acceleration.setX( maxAcceleration*cos((getYAngle() + 90.0f) * 3.1415f / 180.0f) );
	acceleration.setZ( maxAcceleration*sin((getYAngle() + 90.0f) * 3.1415f / 180.0f) );
}
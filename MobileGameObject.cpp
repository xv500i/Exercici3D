#include "MobileGameObject.h"
#include <cmath>
#include "gl\glut.h"

MobileGameObject::MobileGameObject(void) : GameObject()
{
	maxVelocity = 0.9f;
	maxAcceleration = 0.1f;
	friction = 0.95f;
	turnAnglePerStep = 5.0f;
	velocity = Vector3D();
	acceleration = Vector3D();
	footOnGround = false;
	jumpImpulse = false;
	gravity = -0.25f;
	jumpAcceleration = 2.0f;
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
	// gravity here: Gravity < 0 !
	acceleration.setY(gravity);
	velocity += acceleration;
	float velocityY = velocity.getY();
	if (jumpImpulse) {
		velocityY += jumpAcceleration;
		jumpImpulse = false;
	}
	velocity.setY(0.0f);
	if (velocity.getModule() > maxVelocity) {
		// restrict maximum velocity
		velocity.normalize();
		velocity *= maxVelocity;
	}
	velocity *= friction;
	velocity.setY(velocityY);
	setXPosition( getXPosition() + velocity.getX() );
	setZPosition( getZPosition() + velocity.getZ() );
	setYPosition( getYPosition() + velocity.getY() );
	// Friction
	
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

bool MobileGameObject::jump()
{
	if (footOnGround) {
		footOnGround = false;
		jumpImpulse = true;
	}
	return footOnGround;
}

void MobileGameObject::floorReached()
{
	footOnGround = true;
}

void MobileGameObject::render() const
{
	glPushMatrix();
		glDisable(GL_TEXTURE_2D);
		if (footOnGround) {
			glColor3f(0.0f,1.0f,0.0f);
		} else {
			glColor3f(1.0f,0.0f,0.0f);
		}
		// FIXME HARDCODED : radius
		glTranslatef(getXPosition(),getYPosition() + 1.0f,getZPosition());
		glRotatef(-getYAngle(), 0.0f, 1.0f, 0.0f);
		GLUquadricObj *q = gluNewQuadric();
		gluSphere(q, 1,16,16);
		gluDeleteQuadric(q);
		glColor3f(1.0f,1.0f,1.0f);

		if (getDrawAxis()) {
			glLineWidth(3.0f);
			glBegin(GL_LINES);

			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex3f(100.0f, 0.0f, 0.0f);
			glVertex3f(0.0f, 0.0f, 0.0f);

			glColor3f(0.0f, 1.0f, 0.0f);
			glVertex3f(0.0f, 100.0f, 0.0f);
			glVertex3f(0.0f, 0.0f, 0.0f);

			glColor3f(0.0f, 0.0f, 1.0f);
			glVertex3f(0.0f, 0.0f, 100.0f);
			glVertex3f(0.0f, 0.0f, 0.0f);

			glColor3f(1.0f, 1.0f, 1.0f);
			glEnd();
		}
	glPopMatrix();
}

void MobileGameObject::clearYVelocity()
{
	velocity.setY(0.0f);
}
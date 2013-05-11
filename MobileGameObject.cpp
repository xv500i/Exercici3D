#include "MobileGameObject.h"
#include <cmath>
#include "gl\glut.h"

MobileGameObject::MobileGameObject(void) : GameObject()
{
	maxVelocity = 0.5f;
	maxAcceleration = 0.05f;
	friction = 0.98f;
	turnAnglePerStep = 5.0f;
	velocity = Vector3D();
	acceleration = Vector3D();
	footOnGround = false;
	jumpImpulse = false;
	gravity = -0.25f;
	jumpAcceleration = 2.0f;
	type = 'm';
}


MobileGameObject::~MobileGameObject(void)
{
}

void MobileGameObject::update(Vector3D &inclination, std::vector<GameObject*> &objects)
{
	GameObject::update();
	this->inclination = inclination;
	this->inclination.normalize();
	this->inclination*=100.0f;
	// acceleration does not take in account gravity, which is calculated apart!
	if (acceleration.getModule() > maxAcceleration) {
		// restrict maximum acceleration
		acceleration.normalize();
		acceleration *= maxAcceleration;
	}
	// inclination of the terrain
	//acceleration.setX( acceleration.getX() + inclination.getX());
	//acceleration.setZ( acceleration.getZ() + inclination.getZ());
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

	// inclination of the terrain
	velocity.setX( velocity.getX() + inclination.getX());
	velocity.setZ( velocity.getZ() + inclination.getZ());

	setXPosition( getXPosition() + velocity.getX() );
	setZPosition( getZPosition() + velocity.getZ() );
	setYPosition( getYPosition() + velocity.getY() );
	// Friction
	
	// clear accelerations
	acceleration.setX(0.0f);
	acceleration.setY(0.0f);
	acceleration.setZ(0.0f);

	// colisions
	tractarColisions(objects);
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

void MobileGameObject::render(GameData *data) const
{
	glDisable(GL_TEXTURE_2D);
	glPushMatrix();
		
		if (footOnGround) {
			glColor3f(0.0f,1.0f,0.0f);
		} else {
			glColor3f(1.0f,0.0f,0.0f);
		}
		// FIXME HARDCODED : radius
		glTranslatef(getXPosition(),getYPosition() + 1.0f,getZPosition());
		glRotatef(-getYAngle(), 0.0f, 1.0f, 0.0f);
		GLUquadricObj *q = gluNewQuadric();
		gluSphere(q, 1.0f,16,16);
		gluDeleteQuadric(q);
		
	glPopMatrix();
		glColor3f(1.0f,1.0f,1.0f);
		if (getDrawAxis()) {

			glPushMatrix();
			glTranslatef(getXPosition(), getYPosition(), getZPosition());
			glRotatef(-getYAngle(), 0.0f, 1.0f, 0.0f);
			glLineWidth(3.0f);
			glBegin(GL_LINES);

			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex3f(5.0f, 0.0f, 0.0f);
			glVertex3f(0.0f, 0.0f, 0.0f);

			glColor3f(0.0f, 1.0f, 0.0f);
			glVertex3f(0.0f, 5.0f, 0.0f);
			glVertex3f(0.0f, 0.0f, 0.0f);

			glColor3f(0.0f, 0.0f, 1.0f);
			glVertex3f(0.0f, 0.0f, 5.0f);
			glVertex3f(0.0f, 0.0f, 0.0f);

			glColor3f(1.0f, 1.0f, 1.0f);
			glEnd();
			glPopMatrix();
		}
	
	renderBoundingCilinder();

	glDisable(GL_TEXTURE_2D);
	glBegin(GL_LINES);
	
	glVertex3f(getXPosition(), getYPosition(), getZPosition());
	glVertex3f(getXPosition()+inclination.getX(), getYPosition()+inclination.getY(), getZPosition()+inclination.getZ());
	glEnd();
	glEnable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
}

void MobileGameObject::clearYVelocity()
{
	velocity.setY(0.0f);
}

void MobileGameObject::setXVelocity(float v)
{
	velocity.setX(v);
}

void MobileGameObject::setZVelocity(float v)
{
	velocity.setZ(v);
}

void MobileGameObject::tractarColisions(std::vector<GameObject*> &objects)
{
	for(std::vector<GameObject*>::iterator it = objects.begin(); it != objects.end(); ++it) {
		GameObject* go = *it;
		// different object
		if (getId() != go->getId()) {
			if (go->getBoundingCilinder()->isCollisioningWith(*getBoundingCilinder())) {
					jump();
			}
			switch (go->getType()) {	
			case 'g':
				break;
			case 'e':
				break;
			case 'm':
				break;
			case 'p':
				break;
			case 'o':
				break;
			}
		}
	}
}

void MobileGameObject::setYVelocity(float v)
{
	velocity.setY(v);
}
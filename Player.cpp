#include "Player.h"
#include "Globals.h"
#include <iostream>
Player::Player(void)
{
	type = 'p';
	rotX = 0.0f;
	rotY = 0.0f;
	rotZ = 0.0f;
}


Player::~Player(void)
{
}

void Player::render(GameData *data) const 
{
	glEnable(GL_TEXTURE_2D);
	
	glPushMatrix();
		glColor3f(1.0f, 1.0f, 1.0f);
		glBindTexture(GL_TEXTURE_2D, data->getTextureID(GameData::PLAYER_TEXTURE_INDEX));
		glTranslatef(getXPosition(),getYPosition() + 1.0f,getZPosition());
		//glRotatef(-getYAngle(), 0.0f, 1.0f, 0.0f);
		//glRotatef(rotZ, 0.0f , 180.0f * sin( rotX * 3.1415 / 180.0f ) / 3.1415, 180.0f * cos( rotX * 3.1415 / 180.0f ) / 3.1415);
		glRotatef(rotZ, 0.0f, 1.0f , 0.0f);
		glRotatef(rotX, 1.0f, 0.0f, 0.0f);
		
		

		GLUquadricObj *q = gluNewQuadric();
		gluQuadricOrientation(q, GLU_OUTSIDE);
		gluQuadricTexture(q, GL_TRUE);
		gluSphere(q, 1.0f,16,16);
		
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

		gluDeleteQuadric(q);
		
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
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
	Vector3D inclination = getInclination();
	glBegin(GL_LINES);
		glVertex3f(getXPosition(), getYPosition(), getZPosition());
		glVertex3f(getXPosition()+inclination.getX(), getYPosition()+inclination.getY(), getZPosition()+inclination.getZ());
	glEnd();
}

bool Player::isDead()
{
	// FIXME: Natxo aqui has de definir quan el jugador esta mort i cal saltar al game over
	return false;
}

void Player::tractarColisions(std::vector<GameObject*> &objects)
{
	for(std::vector<GameObject*>::iterator it = objects.begin(); it != objects.end(); ++it) {
		GameObject* go = *it;
		// different object
		if (getId() != go->getId()) {
			if (go->getBoundingCilinder()->isCollisioningWith(*getBoundingCilinder())) {
				MobileGameObject * mgo;
				switch (go->getType()) {	
				case 'g':
				
					break;
				case 'e':
					// TODO Damage player and make it invul
					// sliding
					sliding(go);
					mgo = (MobileGameObject *) (go);
					mgo->sliding(this);
					jump();
					break;
				case 'm':
				
					break;
				case 'p':
				
					break;
				case 'o':
					// sliding
					sliding(go);
					break;
				case 'i':
					// TODO recollir 
					break;
				}
			}
		}
	}
}

void Player::update(Vector3D &inclination, std::vector<GameObject*> &objects)
{
	float initialX = getXPosition();
	float initialZ = getZPosition();
	MobileGameObject::update(inclination, objects);
	float finalX = getXPosition();
	float finalZ = getZPosition();
	//                                     2 *   pi    * r
	rotX += (finalZ - initialZ) * 360.0 / (2 * 3.1415f * 1);
	rotZ -= (finalX - initialX) * 360.0 / (2 * 3.1415f * 1);

	std::cout << rotX << ' ' << rotZ << std::endl;
}

void Player::resetRot()
{
	rotZ = 0.0f;
	rotX = 0.0f;
	rotY = 0.0f;
}
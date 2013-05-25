
#include "Player.h"
#include <gl/glut.h>
#include <cmath>
#include "ItemObject.h"

int Player::MAX_TICS_EXPANSION_VERTICAL = 4;
int Player::MAX_TICS_EXPANSION_HORIZONTAL = 3;
int Player::MAX_TICS_UNEXPANSION_VERTICAL = 2;
int Player::MAX_TICS_UNEXPANSION_HORIZONTAL = 2;

Player::Player(void)
{
	type = PLAYER;
	rotX = 0.0f;
	rotY = 0.0f;
	rotZ = 0.0f;
	life = MAX_LIFE;
	ticsInvul = 0;
	expansionState = NO_EXPANDED;
	ticsExpansion = 0;
	jumping = false;
}

Player::~Player(void) {}

void Player::render(GameData &data) const 
{
	if (ticsInvul%8 > 3) return;
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
		glColor3f(1.0f, 1.0f, 1.0f);
		glBindTexture(GL_TEXTURE_2D, data.getTextureID(GameData::PLAYER_TEXTURE_INDEX));
		glTranslatef(getXPosition(),getYPosition() + 1.0f,getZPosition());

		float scaleOffsetVertical = 0.4;
		float scaleOffsetHorizontal = 0.2;
		float init = ticsExpansion;
		float max;
		float interpolation; 
		switch (expansionState){
		case EXPANDING_VERTICAL:
			//          1.0 -> 0.7          1.0 -> 1.3            1.0 -> 0.7
			max = MAX_TICS_EXPANSION_VERTICAL;
			interpolation = scaleOffsetVertical * init / max; // pertany a [0,scaleOffset]  0->fi animacio, 1->inici animacio
			glScalef(0.7f + interpolation, 1.3f - interpolation, 0.7f + interpolation);
			break;
		case UNEXPANDING_VERTICAL:
			//          0.7 -> 1.0          1.3 -> 1.0            0.7 -> 1.0
			max = MAX_TICS_UNEXPANSION_VERTICAL;
			interpolation = scaleOffsetVertical * init / max; // pertany a [0,scaleOffset]  0->fi animacio, 1->inici animacio
			glScalef(1.0f - interpolation, 1.0f + interpolation, 1.0f - interpolation);
			break;
		case EXPANDING_HORIZONTAL:
			//          1.0 -> 1.3          1.0 -> 0.7            1.0 -> 1.3
			max = MAX_TICS_EXPANSION_HORIZONTAL;
			interpolation = scaleOffsetHorizontal * init / max; // pertany a [0,scaleOffset]  0->fi animacio, 1->inici animacio
			glScalef(1.3f - interpolation, 0.7f + interpolation, 1.3f - interpolation);
			break;
		case UNEXPANDING_HORIZONTAL:
			//          1.3 -> 1.0          0.7 -> 1.0            1.3 -> 1.0
			max = MAX_TICS_UNEXPANSION_HORIZONTAL;
			interpolation = scaleOffsetHorizontal * init / max; // pertany a [0,scaleOffset]  0->fi animacio, 1->inici animacio
			glScalef(1.0f + interpolation, 1.0f - interpolation, 1.0f + interpolation);
			break;
		}

		glRotatef(-rotY, 0.0f, 1.0f , 0.0f);
		glRotatef(-rotX, 0.0f , 0.0f, 1.0f);
		

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


int Player::getLife()
{
	return life;
}

bool Player::isDead()
{
	return life == 0;
}

void Player::tractarColisions(std::vector<GameObject*> &objects)
{
	for (std::vector<GameObject*>::iterator it = objects.begin(); it != objects.end(); ++it) {
		GameObject* go = *it;
		// different object
		if (getId() != go->getId()) {
			if (go->getBoundingCilinder()->isCollisioningWith(*getBoundingCilinder())) {
				MobileGameObject *mgo;
				ItemObject *io;
				switch (go->getType()) {	
				case ENEMY:
					// Player HIT
					if (life > 0 && ticsInvul == 0) {
						life--;
						ticsInvul = MAX_TICS_INVUL;
					}
					// sliding
					sliding(go);
					mgo = (MobileGameObject *) (go);
					mgo->sliding(this);
					jump();
					break;
				case OBSTACLE:
					sliding(go);
					break;
				case ENERGY:
					// TODO recollir
					io = (ItemObject *)go;
					io->pickUp();
					break;
				case MEDIKIT:
					if (life < MAX_LIFE) life++;
					io = (ItemObject *)go;
					io->pickUp();
					break;
				case OBJECT: break;
				case MOBILEOBJECT: break;
				case PLAYER: break;
				}
			}
		}
	}
}

void Player::update(Vector3D &inclination, std::vector<GameObject*> &objects)
{
	if (ticsInvul > 0) ticsInvul--;
	if (ticsExpansion > 0) ticsExpansion--;

	/* Expansion */
	switch (expansionState) {
	case NO_EXPANDED:
		break;
	case EXPANDING_HORIZONTAL:
		if (ticsExpansion <= 0) {
			ticsExpansion = MAX_TICS_UNEXPANSION_HORIZONTAL;
			expansionState = UNEXPANDING_HORIZONTAL;
		}
		break;
	case UNEXPANDING_HORIZONTAL:
		if (ticsExpansion <= 0) {
			ticsExpansion = 0;
			expansionState = NO_EXPANDED;
		}
		break;
	case EXPANDING_VERTICAL:
		if (ticsExpansion <= 0) {
			ticsExpansion = MAX_TICS_UNEXPANSION_VERTICAL;
			expansionState = UNEXPANDING_VERTICAL;
		}
		break;
	case UNEXPANDING_VERTICAL:
		if (ticsExpansion <= 0) {
			ticsExpansion = 0;
			expansionState = NO_EXPANDED;
		}
		break;
	}

	float initialX = getXPosition();
	float initialZ = getZPosition();
	MobileGameObject::update(inclination, objects);
	float finalX = getXPosition();
	float finalZ = getZPosition();
	float incZ = (finalZ - initialZ);//     2 *   pi    * r
	float incX = (finalX - initialX);
	rotX += sqrt(incZ*incZ + incX*incX) * 360.0 / (2 * 3.1415f * 1);
	rotY = atan2(incZ, incX) * 180.0f / 3.1415f;
}

void Player::resetRot()
{
	rotZ = 0.0f;
	rotX = 0.0f;
	rotY = 0.0f;
}

bool Player::jump()
{
	bool jumped = MobileGameObject::jump();
	if (jumped) {
		jumping = true;
		expansionState = EXPANDING_VERTICAL;
		ticsExpansion = MAX_TICS_EXPANSION_VERTICAL;
	}
	return jumped;
}

void Player::floorReached()
{
	if (jumping) {
		jumping = false;
		expansionState = EXPANDING_HORIZONTAL;
		ticsExpansion = MAX_TICS_EXPANSION_HORIZONTAL;
	}
	
	MobileGameObject::floorReached();
}
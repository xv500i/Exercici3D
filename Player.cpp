#include "Player.h"
#include "Globals.h"


Player::Player(void)
{
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
		glRotatef(-getYAngle(), 0.0f, 1.0f, 0.0f);

		GLUquadricObj *q = gluNewQuadric();
		gluQuadricOrientation(q, GLU_OUTSIDE);
		gluQuadricTexture(q, GL_TRUE);
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
	
	//renderBoundingCilinder();

	/*glBegin(GL_LINES);
		glVertex3f(getXPosition(), getYPosition(), getZPosition());
		glVertex3f(getXPosition()+inclination.getX(), getYPosition()+inclination.getY(), getZPosition()+inclination.getZ());
	glEnd();*/
}

bool Player::isDead()
{
	// FIXME: Natxo aqui has de definir quan el jugador esta mort i cal saltar al game over
	return false;
}
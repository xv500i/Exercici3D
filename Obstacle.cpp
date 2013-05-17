#include "Obstacle.h"
#include "gl\glut.h"

Obstacle::Obstacle(void)
	: GameObject()
{
	type = 'o';
}


Obstacle::~Obstacle(void)
{

}

Obstacle::Obstacle(float x, float y, float z, float height, float radius, ObstacleType obsType)
	: GameObject(), obsType(obsType)
{
	setXPosition(x);
	setYPosition(y);
	setZPosition(z);
	BoundingCilinder *bc = getBoundingCilinder();
	bc->setHeight(height);
	bc->setRadius(radius);
	type = 'o';
}
	
void Obstacle::render(GameData *data) const
{
	// TODO BILLBOARD
	glPushMatrix();
		glDisable(GL_TEXTURE_2D);
		glColor3f(1.0f,1.0f,1.0f);
		// FIXME HARDCODED : radius

		glTranslatef(getXPosition(),getYPosition(),getZPosition());
		GLUquadricObj *q = gluNewQuadric();
		gluSphere(q, 1,16,16);

		gluDeleteQuadric(q);
		glColor3f(1.0f,1.0f,1.0f);

		

	glPopMatrix();
	renderBoundingCilinder();
	glEnable(GL_TEXTURE_2D);
	
}

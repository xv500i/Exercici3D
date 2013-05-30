
#include "Landscape.h"


Landscape::Landscape() {}

Landscape::Landscape(int textureIndex) : rotation(0.0f), textureIndex(textureIndex) 
{
	createLandscape();
}

Landscape::~Landscape(void) {}


/* Update */
void Landscape::update()
{
	rotation += 0.05;
}


/* Render */
void Landscape::render(GameData &data)
{
	glEnable(GL_TEXTURE_2D);	
	glPushMatrix();
		glColor3f(1.0f, 1.0f, 1.0f);
		glBindTexture(GL_TEXTURE_2D, data.getTextureID(textureIndex));
		//glTranslatef(getXPosition(),getYPosition() + 1.0f,getZPosition());
		glRotatef(rotation, 0.0f, 1.0f, 0.0f);
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		glCallList(LANDSCAPE);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}


/* Displaylist creation */
void Landscape::createLandscape()
{
	glNewList(LANDSCAPE, GL_COMPILE);
		GLUquadricObj *q = gluNewQuadric();
		gluQuadricOrientation(q, GLU_OUTSIDE);
		gluQuadricTexture(q, GL_TRUE);
		gluSphere(q, 240.0f, 16, 16);
		gluDeleteQuadric(q);
	glEndList();
}
#include "Altar.h"


Altar::Altar(void) : GameObject() 
{
	type = ALTAR;
	active = false;
	BoundingCilinder *bc = getBoundingCilinder();
	bc->setHeight(6.0f);
}

Altar::~Altar(void) {}


/* Render */
void Altar::render(GameData &data)
{
	Point3D pos = getPosition();
	glPushMatrix();
		GLUquadricObj *q1 = gluNewQuadric();
		GLUquadricObj *q2 = gluNewQuadric();
		GLUquadricObj *q3 = gluNewQuadric();

		glTranslatef(pos.getX(), pos.getY() + 1.0f, pos.getZ());
		if (active) glColor3f(1.0f, 1.0f, 0.0f);
		else glColor3f(1.0f, 0.0f, 0.0f);
		gluSphere(q1, 1, 16, 16);
		gluDeleteQuadric(q1);

		glTranslatef(0.0f, 2.0f, 0.0f);
		if (active) glColor3f(1.0f, 1.0f, 0.0f);
		else glColor3f(0.0f, 1.0f, 0.0f);
		gluSphere(q2, 1, 16, 16);
		gluDeleteQuadric(q2);

		glTranslatef(0.0f, 2.0f, 0.0f);
		if (active) glColor3f(1.0f, 1.0f, 0.0f);
		else glColor3f(0.0f, 0.0f, 1.0f);
		gluSphere(q3, 1, 16, 16);
		gluDeleteQuadric(q3);

		glColor3f(1.0f, 1.0f, 1.0f);
	glPopMatrix();

	renderBoundingCilinder();
}


/* Altar activation */
void Altar::activate()
{
	active = true;
}

bool Altar::isActive()
{
	return active;
}
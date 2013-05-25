#include "ItemObject.h"


ItemObject::ItemObject() : GameObject() {}

ItemObject::ItemObject(bool energy) : GameObject()
{
	if (energy) type = ENERGY;
	else type = MEDIKIT;
	pickedUp = false;
}

ItemObject::~ItemObject(void) {}


/* Render */
void ItemObject::render()
{
	if (pickedUp) return;
	Point3D pos = getPosition();
	glPushMatrix();
		glColor3f(0.0f, 1.0f, 0.0f);
		glTranslatef(pos.getX(), pos.getY() + 1.0f, pos.getZ());
		GLUquadricObj *q = gluNewQuadric();
		gluSphere(q, 0.5, 16, 16);
		gluDeleteQuadric(q);

		glColor3f(1.0f,1.0f,1.0f);
	glPopMatrix();
}


/* Pick up */
void ItemObject::pickUp()
{
	pickedUp = true;
}

bool ItemObject::isPickedUp()
{
	return pickedUp;
}
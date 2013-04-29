#include "GameObject.h"
#include "gl\glut.h"

bool GameObject::drawAxis = true;

GameObject::GameObject(void)
{
	pos = Point3D();
	yAngle = 0.0f;
	movementState = STATIC;
}


GameObject::~GameObject(void)
{
}

Point3D GameObject::getPosition() const
{
	return pos;
}

float GameObject::getXPosition() const
{
	return pos.getX();
}

float GameObject::getYPosition() const
{
	return pos.getY();
}

float GameObject::getZPosition() const
{
	return pos.getZ();
}

float GameObject::getYAngle() const
{
	return yAngle;
}

void GameObject::update()
{

}

void GameObject::render() const
{
	glPushMatrix();
		glDisable(GL_TEXTURE_2D);
		glColor3f(1.0f,1.0f,1.0f);
		// FIXME HARDCODED : radius
		glTranslatef(pos.getX(),pos.getY() + 1.0f,pos.getZ());
		glRotatef(-yAngle, 0.0f, 1.0f, 0.0f);
		GLUquadricObj *q = gluNewQuadric();
		gluSphere(q, 1,16,16);
		gluDeleteQuadric(q);
		glColor3f(1.0f,1.0f,1.0f);

		if (drawAxis) {
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

void GameObject::setYAngle(float newYAngle)
{
	yAngle = newYAngle;
}

void GameObject::setXPosition(float v)
{
	pos.setX(v);
}

void GameObject::setYPosition(float v)
{
	pos.setY(v);
}

void GameObject::setZPosition(float v)
{
	pos.setZ(v);
}

#include "GameObject.h"
#include <gl\glut.h>
// DEBUG
#include "Globals.h"


bool GameObject::drawAxis = true;
int GameObject::idCounter = 0;

GameObject::GameObject(void)
{
	id = idCounter++;
	type = OBJECT;
	pos = Point3D();
	yAngle = 0.0f;
	movementState = STATIC;
	bc = new BoundingCilinder(0.0f, 0.0f, 0.0f, 2.0f, 1.0f);
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

void GameObject::render(GameData &data) const
{
	glPushMatrix();
		glColor3f(1.0f,1.0f,1.0f);

		glTranslatef(pos.getX(),pos.getY() + 1.0f,pos.getZ());
		glRotatef(-yAngle, 0.0f, 1.0f, 0.0f);
		GLUquadricObj *q = gluNewQuadric();
		gluSphere(q, 1,16,16);

		gluDeleteQuadric(q);
		glColor3f(1.0f,1.0f,1.0f);

		if (DEBUG) {
			// Axis
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
	bc->setCenterX(v);
	pos.setX(v);
}

void GameObject::setYPosition(float v)
{
	bc->setCenterY(v);
	pos.setY(v);
}

void GameObject::setZPosition(float v)
{
	bc->setCenterZ(v);
	pos.setZ(v);
}

bool GameObject::getDrawAxis() const
{
	return drawAxis;
}

void GameObject::setDrawAxis(bool b)
{
	drawAxis = b;
}

void GameObject::renderBoundingCilinder() const
{
	GLUquadricObj *cylinder = gluNewQuadric();
	
	glColor3f(1.0f,1.0f,1.0f);
	glPushMatrix();
	glTranslatef(bc->getX() ,bc->getY(), bc->getZ());
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	// FIXME perque no trenqui la esfera
	gluQuadricDrawStyle(cylinder, GLU_LINE);
	gluCylinder(cylinder, bc->getRadius(), bc->getRadius(), bc->getHeight(), 8, 2);
	glPopMatrix();
	gluDeleteQuadric(cylinder);

}

BoundingCilinder* GameObject::getBoundingCilinder()
{
	return bc;
}

int GameObject::getId()
{
	return id;
}

ObjectType GameObject::getType()
{
	return type;
}
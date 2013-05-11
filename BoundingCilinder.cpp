#include "BoundingCilinder.h"


BoundingCilinder::BoundingCilinder(void)
	: center()
{
	h = 0.0f;
}


BoundingCilinder::~BoundingCilinder(void)
{
}

BoundingCilinder::BoundingCilinder(float x, float y, float z, float height, float radius)
	: center(x,y,z), h(height), r(radius)
{

}

void BoundingCilinder::setCenter(float x, float y, float z)
{
	center.setX(x);
	center.setY(y);
	center.setZ(z);
}

void BoundingCilinder::setHeight(float v)
{
	h = v;
}

float BoundingCilinder::getHeight() const
{
	return h;
}

float BoundingCilinder::getX() const
{
	return center.getX();
}

float BoundingCilinder::getY() const
{
	return center.getY();
}

float BoundingCilinder::getZ() const
{
	return center.getZ();
}

bool BoundingCilinder::isCollisioningWith(const BoundingCilinder &bc)
{
	//            this a sota de bc                     bc sota de this
	if (center.getY() + h  < bc.center.getY() || center.getY() > bc.center.getY() + bc.getHeight()) return false;
	else if (center.distanceTo(bc.center) >= r + bc.r) return false;
	return true;
}

float BoundingCilinder::getRadius() const
{
	return r;
}

void BoundingCilinder::setRadius(float v)
{
	r = v;
}

void BoundingCilinder::setCenterX(float x)
{
	center.setX(x);
}

void BoundingCilinder::setCenterY(float y)
{
	center.setY(y);
}

void BoundingCilinder::setCenterZ(float z)
{
	center.setZ(z);
}
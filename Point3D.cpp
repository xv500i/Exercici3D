#include "Point3D.h"
#include "Vector3D.h"
#include <cmath>

Point3D::Point3D(void) : x(0.0f),y(0.0f),z(0.0f)
{

}

Point3D::Point3D(float x, float y, float z) : x(x), y(y), z(z)
{

}

Point3D::~Point3D(void)
{

}

float Point3D::getX() const
{
	return x;
}

float Point3D::getY() const
{
	return y;
}

float Point3D::getZ() const
{
	return z;
}

Point3D Point3D::operator+=(const Vector3D &p)
{
	increment(p.getX(), p.getY(), p.getZ());
	return *this;
}

Point3D Point3D::operator-=(const Vector3D &p)
{
	increment(-p.getX(), -p.getY(), -p.getZ());
	return *this;
}

void Point3D::increment(float ix, float iy, float iz)
{
	x+=ix;
	y+=iy;
	z+=iz;
}

void Point3D::setX(float v)
{
	x = v;
}

void Point3D::setY(float v)
{
	y = v;
}

void Point3D::setZ(float v)
{
	z = v;
}

float Point3D::distanceTo(const Point3D &p) const
{
	Vector3D aux = Vector3D(x-p.x, y-p.y, z-p.z);
	return aux.getModule();
}
#include "Point3D.h"

Point3D::Point3D(void)
{
	x = y = z = 0.0f;
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

Point3D Point3D::operator+(const Point3D &p) const
{
	return Point3D(x+p.x, y+p.y,z+p.z);
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
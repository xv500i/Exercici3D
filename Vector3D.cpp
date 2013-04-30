#include "Vector3D.h"
#include <cmath>

Vector3D::Vector3D(void) : x(0.0f),y(0.0f),z(0.0f)
{
}

Vector3D::Vector3D(float x, float y, float z) : x(x), y(y), z(z)
{

}


Vector3D::~Vector3D(void)
{
}

float Vector3D::getModule() const
{
	return sqrt( x*x + y*y + z*z );
}

Vector3D Vector3D::operator-(const Vector3D &v) const
{
	return Vector3D(x-v.x, y-v.y, z-v.z);
}

Vector3D Vector3D::operator+(const Vector3D &v) const
{
	return Vector3D(x+v.x, y+v.y, z+v.z);
}

Vector3D Vector3D::operator-=(const Vector3D &v)
{
	x-=v.x;
	y-=v.y;
	z-=v.z;
	return *this;
}

Vector3D Vector3D::operator+=(const Vector3D &v)
{
	x+=v.x;
	y+=v.y;
	z+=v.z;
	return *this;
}

Vector3D Vector3D::operator*=(float factor)
{
	x*=factor;
	y*=factor;
	z*=factor;
	return *this;
}

Vector3D Vector3D::operator/=(float factor)
{
	x/=factor;
	y/=factor;
	z/=factor;
	return *this;
}

Vector3D Vector3D::normalize()
{
	*this /= getModule();
	return *this;
}

Vector3D Vector3D::rotate(float alfa, float beta)
{
	//FIXME
	return Vector3D();
}

Vector3D* Vector3D::vectorialProduct(const Vector3D &v) const
{
	Vector3D *res = new Vector3D( y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x);
	return res;
}

float Vector3D::getX() const
{
	return x;
}

float Vector3D::getY() const
{
	return y;
}

float Vector3D::getZ() const
{
	return z;
}

void Vector3D::setX(float v)
{
	x = v;
}

void Vector3D::setY(float v)
{
	y = v;
}

void Vector3D::setZ(float v)
{
	z = v;
}

void Vector3D::setPolar(float module, float alfa, float beta)
{
	// FIXME
}

void Vector3D::getPolar(float &module, float &alfa, float &beta)
{
	// FIXME
}
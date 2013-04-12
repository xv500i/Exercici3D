#pragma once
#include "Vector3D.h"
class Point3D
{
public:
	Point3D(void);
	Point3D(float x, float y, float z);
	~Point3D(void);
	Point3D operator+=(const Vector3D &p);
	Point3D operator-=(const Vector3D &p);
	float getX() const;
	float getY() const;
	float getZ() const;
	void setX(float v);
	void setY(float v);
	void setZ(float v);
	void increment(float ix, float iy, float iz);
private:
	float x;
	float y;
	float z;
};


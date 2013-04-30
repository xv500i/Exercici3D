#pragma once
#include "Point3D.h"
class BoundingCilinder
{
public:
	BoundingCilinder(void);
	BoundingCilinder(float x, float y, float z, float height, float radius);
	~BoundingCilinder(void);
	void setCenter(float x, float y, float z);
	void setCenterX(float x);
	void setCenterY(float y);
	void setCenterZ(float z);
	void setHeight(float v);
	void setRadius(float v);
	float getHeight() const;
	float getX() const;
	float getY() const;
	float getZ() const;
	float getRadius() const;
	bool isCollisioningWith(const BoundingCilinder &bc);
private:
	Point3D center;
	float h;
	float r;
};


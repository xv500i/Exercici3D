#pragma once
class Point3D
{
public:
	Point3D(void);
	Point3D(float x, float y, float z);
	~Point3D(void);
	Point3D operator+(const Point3D &p) const;
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


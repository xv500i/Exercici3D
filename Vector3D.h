#pragma once
class Vector3D
{
public:
	Vector3D(void);
	Vector3D(float x, float y, float z);
	~Vector3D(void);
	float getModule() const;
	Vector3D operator-(const Vector3D &v) const;
	Vector3D operator+(const Vector3D &v) const;
	Vector3D operator-=(const Vector3D &v);
	Vector3D operator+=(const Vector3D &v);
	Vector3D operator*=(float factor);
	Vector3D operator/=(float factor);
	Vector3D normalize();
	Vector3D rotate(float alfa, float beta);
	Vector3D vectorialProduct(const Vector3D &v) const;
	float getX() const;
	float getY() const;
	float getZ() const;
	void setX(float v);
	void setY(float v);
	void setZ(float v);
	void setPolar(float module, float alfa, float beta);
	void getPolar(float &module, float &alfa, float &beta);
	
private:
	float x;
	float y;
	float z;
};


#pragma once
#include "MovementState.h"
#include "Point3D.h"
class GameObject
{
public:
	GameObject(void);
	~GameObject(void);
	Point3D getPosition() const;
	float getXPosition() const;
	float getYPosition() const;
	float getZPosition() const;
	void setXPosition(float v);
	void setYPosition(float v);
	void setZPosition(float v);
	void update();
	void render() const;
	float getYAngle() const;
	void setYAngle(float newYAngle);
	bool getDrawAxis() const;
	void setDrawAxis(bool b);
private:
	static bool drawAxis;
	Point3D pos;
	float yAngle;
	MovementState movementState;
};


#pragma once
#include "MovementState.h"
#include "BoundingCilinder.h"
#include "Point3D.h"
#include "GameData.h"


enum ObjectType {
	OBJECT,
	MOBILEOBJECT,
	OBSTACLE,
	ALTAR,
	PLAYER,
	ENEMY,
	MEDIKIT,
	ENERGY
};


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
	void render(GameData &data) const;
	float getYAngle() const;
	void setYAngle(float newYAngle);
	bool getDrawAxis() const;
	void setDrawAxis(bool b);
	void renderBoundingCilinder() const;
	BoundingCilinder* getBoundingCilinder();
	int getId();
	ObjectType getType();
private:
	static int idCounter;
	int id;
	static bool drawAxis;
	Point3D pos;
	float yAngle;
	MovementState movementState;
	BoundingCilinder *bc;
protected:
	ObjectType type;
};


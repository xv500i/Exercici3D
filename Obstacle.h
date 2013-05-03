#pragma once
#include "gameobject.h"

enum ObstacleType{
	TREE,
	BARREL
};

class Obstacle :
	public GameObject
{
public:
	Obstacle(void);
	Obstacle(Point3D &center, float height, float radius, ObstacleType type);
	~Obstacle(void);
	void render() const;
	void update();
private:
	float height;
	float radius;
};


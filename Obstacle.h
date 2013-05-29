
#pragma once

#include "GameObject.h"


enum ObstacleType {
	COLUMN,
	BARREL
};


class Obstacle :
	public GameObject
{
public:
	Obstacle(void);
	Obstacle(float x, float y, float z, ObstacleType obsType);
	~Obstacle(void);
	void render(GameData &data);

private:
	ObstacleType obsType;
};
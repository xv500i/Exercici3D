#pragma once
#include "GameObject.h"

enum ObstacleType{
	TREE,
	BARREL
};

class Obstacle :
	public GameObject
{
public:
	Obstacle(void);
	Obstacle(float x, float y, float z, float height, float radius, ObstacleType type);
	~Obstacle(void);
	void render(GameData *data) const;
private:
	ObstacleType type;
};


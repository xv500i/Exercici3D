
#pragma once

#include "GameObject.h"

// PROVA
#include "Model.h"

enum ObstacleType {
	TREE,
	BARREL
};


class Obstacle :
	public GameObject
{
public:
	Obstacle(void);
	Obstacle(float x, float y, float z, float height, float radius, ObstacleType obsType);
	~Obstacle(void);
	void render(GameData &data);

private:
	ObstacleType obsType;
	Model model;
};
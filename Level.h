
#pragma once

#include <vector>
#include "PixelBasedFloor.h"
#include "Player.h"
#include "Enemy.h"
#include "Obstacle.h"
#include "Landscape.h"
#include "GameData.h"


class Level
{
private:
	PixelBasedFloor map;				/* The level map */
	std::vector<Enemy> enemies;			/* Vector with all the enemies of the level */
	std::vector<Obstacle> obstacles;	/* Vector with all the obstacles of the level */
	Landscape landscape;

	/* Loading of different levels */
	void loadFirstLevel();
	void loadSecondLevel();
	void loadThirdLevel();

public:
	Level(void);
	virtual ~Level(void);

	/* Level loading */
	void load(int level);

	/* Update */
	void update(Player &player);

	/* Render */
	void render(GameData &data);
};
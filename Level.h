
#pragma once

#include <vector>
#include "PixelBasedFloor.h"
#include "Player.h"
#include "Enemy.h"
#include "Obstacle.h"
#include "Altar.h"
#include "EnergyObject.h"
#include "MediKitObject.h"
#include "Landscape.h"
#include "GameData.h"
#include "CameraHandler.h"


class Level
{
private:
	PixelBasedFloor map;					/* The level map */
	std::vector<Enemy> enemies;				/* Vector with all the enemies of the level */
	std::vector<Obstacle> obstacles;		/* Vector with all the obstacles of the level */
	std::vector<Altar> altars;				/* Vector with all the altars of the level */
	std::vector<EnergyObject> energies;		/* Vector with all the energies of the level */
	std::vector<MediKitObject> medikits;	/* Vector with all the medikits of the level */
	Landscape landscape;

	/* Loading of different levels */
	void loadFirstLevel();
	void loadSecondLevel();
	void loadThirdLevel();
	
	bool fusRoDahUsed;


public:
	Level(void);
	virtual ~Level(void);

	/* Level loading */
	void load(int level);

	/* Update */
	void update(CameraHandler &camera, Player &player);

	/* Render */
	void render(GameData &data);

	/* Level completed */
	bool isLevelCompleted();

	void useFusRoDah();
};
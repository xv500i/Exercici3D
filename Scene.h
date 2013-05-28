
#pragma once

#include <vector>
#include "GameData.h"
#include "InputHandler.h"
#include "CameraHandler.h"
#include "Player.h"
#include "HUD.h"
#include "Level.h"


class Scene
{
private:
	const static int NUM_LEVELS = 3;

	HUD hud;		/* HUD (player life & items) */
	Player player;	/* The player */
	Level level;	/* The level */
	
	int currentLevel;
	bool isCurrentLevelCompleted;

public:
	Scene(void);
	virtual ~Scene(void);

	/* Scene initialization */
	bool init(int screenWidth, int screenHeight);

	/* Update */
	void resolveInput(InputHandler &input);
	void update(CameraHandler &camera);

	/* Render */
	void render(GameData &data);

	bool playerIsDead();
	void loadLevel(int levelNumber);
	void nextLevel();
	bool isLevelCompleted();
	bool isLastLevel();
	void resetRot();
	int getCurrentLevel();
};

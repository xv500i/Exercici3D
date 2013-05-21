#pragma once

#include "GameData.h"
//#include "cData.h"
#include "Player.h"
#include "InputHandler.h"
#include "CameraHandler.h"
#include "PixelBasedFloor.h"
#include "Enemy.h"
#include <vector>
#include "Obstacle.h"

#define SCENE_WIDTH		16
#define SCENE_DEPTH		32
#define SCENE_HEIGHT	 4

class Scene
{
public:
	Scene(void);
	virtual ~Scene(void);

	bool Init();
	bool drawEntity(bool draw);
	//void Draw(cData *Data);
	void render(GameData &gd);
	void update(InputHandler &input, CameraHandler &camera);
	void getFirstPersonParameters(float &eyex, float &eyey, float &eyez, float &centerx, float &centery, float &centerz) const;
	bool playerIsDead();
	void loadLevel(int lvl);
	void nextLevel();
	bool isLevelCompleted();
	bool isLastLevel();
private:
	Player go;
	bool drawPlayer;
	PixelBasedFloor *pbf;
	std::vector<Enemy> enemies;
	std::vector<Obstacle> obstacles;
	float landscapeRot;
};

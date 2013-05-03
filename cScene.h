#pragma once

#include "GameData.h"
//#include "cData.h"
#include "MobileGameObject.h"
#include "InputHandler.h"
#include "PixelBasedFloor.h"
#include "Enemy.h"
#include <vector>
#include "Obstacle.h"

#define SCENE_WIDTH		16
#define SCENE_DEPTH		32
#define SCENE_HEIGHT	 4

class cScene
{
public:
	cScene(void);
	virtual ~cScene(void);

	bool Init();
	bool drawEntity(bool draw);
	//void Draw(cData *Data);
	void render(GameData &gd);
	void update(InputHandler &input);
	void getFirstPersonParameters(float &eyex, float &eyey, float &eyez, float &centerx, float &centery, float &centerz) const;
private:
	MobileGameObject go;
	bool drawPlayer;
	PixelBasedFloor *pbf;
	std::vector<Enemy> enemies;
	std::vector<Obstacle> obstacles;
};

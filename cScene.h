#pragma once

#include "cData.h"
#include "MobileGameObject.h"
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
	void Draw(cData *Data);
	void resolveInput(unsigned char *keys);
	void getFirstPersonParameters(float &eyex, float &eyey, float &eyez, float &centerx, float &centery, float &centerz) const;
private:
	MobileGameObject go;
	bool drawPlayer;
};

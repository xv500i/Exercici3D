
#pragma once

#include "MobileGameObject.h"
#include "GameData.h"


class Player : public MobileGameObject
{
private:
	const static int MAX_TICS_INVUL = 50;

	float rotX;
	float rotZ;
	float rotY;

	int life;
	int ticsInvul;

public:
	const static int MAX_LIFE = 3;

	Player(void);
	~Player(void);

	void render(GameData &data) const;
	int getLife();
	bool isDead();
	void update(Vector3D &inclination, std::vector<GameObject*> &objects);
	void resetRot();

protected:
	virtual void tractarColisions(std::vector<GameObject*> &objects);
};


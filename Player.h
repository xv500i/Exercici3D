
#pragma once

#include "MobileGameObject.h"
#include "GameData.h"

enum ExpansionState {
	EXPANDING_VERTICAL,
	UNEXPANDING_VERTICAL,
	EXPANDING_HORIZONTAL,
	UNEXPANDING_HORIZONTAL,
	NO_EXPANDED
};

class Player : public MobileGameObject
{
private:
	const static int MAX_TICS_INVUL = 50;
	const static int MAX_TICS_EXPANSION = 5;

	float rotX;
	float rotZ;
	float rotY;

	int life;
	int ticsInvul;
	int ticsExpansion;
	ExpansionState expansionState;
	bool jumping;
	

public:
	const static int MAX_LIFE = 3;

	Player(void);
	~Player(void);

	void render(GameData &data) const;
	int getLife();
	bool isDead();
	void update(Vector3D &inclination, std::vector<GameObject*> &objects);
	void resetRot();
	bool jump();
	void floorReached();

protected:
	virtual void tractarColisions(std::vector<GameObject*> &objects);
};


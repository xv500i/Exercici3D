
#pragma once

#include "MobileGameObject.h"
#include "GameData.h"
#include "Particles.h"


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
	static int MAX_TICS_EXPANSION_VERTICAL;
	static int MAX_TICS_EXPANSION_HORIZONTAL;
	static int MAX_TICS_UNEXPANSION_VERTICAL;
	static int MAX_TICS_UNEXPANSION_HORIZONTAL;


	float rotX;
	float rotZ;
	float rotY;

	/* Player health */
	int life;
	int ticsInvul;

	/* Player energy */
	int energy;

	/* Fus Ro Dah particles */
	Particles particles;
	bool particlesCreated;

	int ticsExpansion;
	ExpansionState expansionState;
	bool jumping;
	int fusRoDahReuse;
	

public:
	const static int MAX_LIFE = 3;

	Player(void);
	~Player(void);

	/* Update */
	void update(Vector3D &inclination, std::vector<GameObject*> &objects, float visionYAngle);

	/* Render */
	void render(GameData &data) const;

	/* Player health */
	int getLife();
	bool isDead();

	/* Player energy */
	int getEnergy();

	void resetRot();
	bool jump();
	void floorReached();
	bool useFusRoDah();
	void fusRoDah();

protected:
	virtual void tractarColisions(std::vector<GameObject*> &objects);
};



#pragma once

#include "GameObject.h"
#include "GameData.h"
#include "Particles.h"


class ItemObject : public GameObject
{
private:
	Particles particles;
	bool particlesCreated;
	bool pickedUp;

public:
	ItemObject();
	ItemObject(bool energy);
	virtual ~ItemObject(void);

	/* Update */
	void update();

	/* Render */
	void render(GameData &data);

	/* Pick up */
	void pickUp();
	bool isPickedUp();
};
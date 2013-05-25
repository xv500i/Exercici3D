
#pragma once

#include "GameObject.h"
#include "GameData.h"


class ItemObject : public GameObject
{
private:
	bool pickedUp;

public:
	ItemObject();
	ItemObject(bool energy);
	virtual ~ItemObject(void);

	/* Render */
	void render(GameData &data);

	/* Pick up */
	void pickUp();
	bool isPickedUp();
};
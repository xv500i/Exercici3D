
#pragma once

#include "GameObject.h"


class ItemObject : public GameObject
{
private:
	bool pickedUp;

public:
	ItemObject();
	ItemObject(bool energy);
	virtual ~ItemObject(void);

	/* Render */
	void render();

	/* Pick up */
	void pickUp();
	bool isPickedUp();
};